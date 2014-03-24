#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "packet.h"


#define USAGE "Usage:\r\nc [tux machine number] [probability of packet corruption in int form] [probability of packet loss in int form]\r\n"
#define BUFSIZE 121
#define FILENAME "Testfile"
#define TEST_FILENAME "Testfile2"

using namespace std;
bool gremlin(Packet * pack, int corruptProb, int lossProb);

bool seqNum;

int main(int argc, char** argv) {
  
  int s = 0;

  if(argc != 4) { 
    cout << USAGE << endl;
    return 1;
  }

  char * probCorruptStr = argv[2];
  int probCorrupt = boost::lexical_cast<int>(probCorruptStr);
  char * probLossStr = argv[3];
  int probLoss = boost::lexical_cast<int>(probLossStr);

  string hs = string("131.204.14.") + argv[1]; /* Needs to be updated? Might be a string like "tux175.engr.auburn.edu." */
  short int port = 10038; /* Can be any port within 10038-10041, inclusive. */
  
  ifstream is (FILENAME, ifstream::binary);

  unsigned char b[BUFSIZE]; 
  char * file;
  int length;

  if(is) {
    is.seekg(0, is.end);
    length = is.tellg();
    is.seekg(0, is.beg);

    file = new char[length];

    cout << "Reading " << length << " characters..." << endl;
    is.read(file, length);

    if(!is) cout << "File reading failed. (filename " << FILENAME << "). Only " << is.gcount() << " could be read.";
    is.close();
  }

  struct sockaddr_in a;
  struct sockaddr_in sa;
  socklen_t salen = sizeof(sa);
  struct hostent *h;

  string m = string("Hello, server world! I'm gonna talk for a long long time and see if this works. Maybe \r\n")
      + "it'll properly tell me there are more bytes; maybe it won't. Either way I'll be proud of the work I've done. \r\n"
      + "Also, Patrick is gay.";

  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    cout << "Socket creation failed. (socket s)" << endl;
    return 0;
  }

  memset((char *)&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY); //why does this always give us 0? 
  a.sin_port = htons(0);

  if (bind(s, (struct sockaddr *)&a, sizeof(a)) < 0){
    cout << "Socket binding failed. (socket s, address a)" << endl;
    return 0;
  }

  memset((char *)&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  inet_pton(AF_INET, hs.c_str(), &(sa.sin_addr));

  cout << endl;

  cout << "Server address (inet mode): " << inet_ntoa(sa.sin_addr) << endl;
  cout << "Port: " << ntohs(sa.sin_port) << endl;

  cout << endl << endl;

  string fstr = string(file);

  cout << "File: " << endl << fstr << endl << endl;

  seqNum = true;
  bool dropPck = false;
  for(int x = 0; x <= length / BUFSIZE; x++) {
    cout << endl;
    cout << "=== TRANSMISSION START" << endl;
    string mstr = fstr.substr(x * BUFSIZE, BUFSIZE);
    if(x * BUFSIZE + BUFSIZE > length) {
      mstr[length - (x * BUFSIZE)] = '\0';
    }
    Packet p(seqNum, mstr.c_str());

    if((dropPck = gremlin(&p, probCorrupt, probLoss)) == false){
      if(sendto(s, p.str(), BUFSIZE + 7, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        cout << "Package sending failed. (socket s, server address sa, message m)" << endl;
        return 0;
      }
    } else continue;

    recvfrom(s, b, BUFSIZE + 7, 0, (struct sockaddr *)&sa, &salen);
    char * ack = new char[3];

    cout << endl << "=== SERVER RESPONSE TEST" << endl;
    cout << "Data: " << b << endl;
    if(b[6] == '0') ack = (char *)"ACK";
    else ack = (char *)"NAK";
    cout << "Response: " << ack << endl;

    if(ack == "NAK") { //if NAK
      /* should say: if chksm(). chksm should be a function both client and server 
       * can see and use that returns a boolean: true if the checksum "checks out" 
       * (no bytes have been tampered with). 
      */

      char * sns = new char[2];
      memcpy(sns, &b[0], 1);
      sns[1] = '\0';

      char * css = new char[5];
      memcpy(css, &b[1], 5);
      
      char * db = new char[BUFSIZE + 1];
      memcpy(db, &b[2], BUFSIZE);
      db[BUFSIZE] = '\0';

      cout << "Sequence number: " << sns << endl;
      cout << "Checksum: " << css << endl;

      Packet pk (0, db);
      pk.setSequenceNum(boost::lexical_cast<int>(sns));
      pk.setCheckSum(boost::lexical_cast<int>(css));

      if(!pk.chksm()) x--; 
      else x = (x - 2 > 0) ? x - 2 : 0;
    }

    memset(b, 0, BUFSIZE);
  }

  return 0;
}
bool gremlin(Packet * pack, int corruptProb, int lossProb){
  bool dropPacket = false;
  int r = rand() % 100;

  if(r <= (lossProb)){
    dropPacket = true;
    cout << "Dropped!" << endl;
  }  
  else if(r <= (corruptProb)){
    cout << "Corrupted!" << endl;
    pack->loadDataBuffer((char*)"GREMLIN LOL");
  }
  else seqNum = (seqNum) ? false : true; 
  cout << "Seq. num: " << pack->getSequenceNum() << endl;
  cout << "Checksum: " << pack->getCheckSum() << endl;
  cout << "Message: "  << pack->getDataBuffer() << endl;

  return dropPacket;
}
