#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "packet.h"

#define PORT 10038
#define PAKSIZE 128
#define ACK "ACK"
#define NAK "NAK"

using namespace std;

bool seqNum;

bool isvpack(unsigned char * p) {

  char * css = new char[6];
  memcpy(css, &p[1], 5);
  css[6] = '\0';

  int cs = boost::lexical_cast<int>(css);

  char * db = new char[126];

  strcpy(db, reinterpret_cast<const char *>(p)+7);

  Packet pk (0, db);
  pk.setSequenceNum(0);

  // change to validate based on checksum and sequence number
  //if((bool)p[0] == seqNum) return false;
  if(cs != pk.generateCheckSum()) return false;
  return true;
}

int main() {
  struct sockaddr_in a;
  struct sockaddr_in ca;
  socklen_t calen = sizeof(ca);
  int rlen;
  int s;
  string ack;
  seqNum = true;

  /* Create our socket. */
  if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    cout << "Socket creation failed. (socket s)" << endl;
    return 0;
  }

  /* 
   * Bind our socket to an IP (whatever the computer decides) 
   * and a specified port. 
   *
   */

  memset((char *)&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = htons(PORT);

  if (bind(s, (struct sockaddr *)&a, sizeof(a)) < 0) {
    cout << "Socket binding failed. (socket s, address a)" << endl;
    return 0;
  }

  /* Loop forever, waiting for messages from a client. */

  cout << "Waiting on port " << PORT << "..." << endl;

  ofstream file("Dumpfile");

  for (;;) {
    unsigned char packet[PAKSIZE + 1];
    unsigned char dataPull[PAKSIZE - 7 + 1];
    rlen = recvfrom(s, packet, PAKSIZE, 0, (struct sockaddr *)&ca, &calen);
    for(int x = 0; x < PAKSIZE - 7; x++) {
      dataPull[x] = packet[x + 7];
    }
    dataPull[PAKSIZE - 7] = '\0';
    packet[PAKSIZE] = '\0';
    cout << "Received " << rlen << " bytes." << endl;
    if (rlen > 0) {
      cout << "Received message: " << endl << packet << endl;
      if(isvpack(packet)) {
        ack = "ACK";
        file << dataPull;
      } else { 
        ack = "NAK";
      }
      if(sendto(s, ack.c_str(), strlen(ack.c_str()), 0, (struct sockaddr *)&ca, calen) < 0) {
        cout << "Acknowledgement failed. (socket s, acknowledgement message ack, client address ca, client address length calen)" << endl;
        return 0;
      }
    }
  }
  file.close();
}
