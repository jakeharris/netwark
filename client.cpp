#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "packet.h"


#define USAGE "Usage:\r\nc [tux machine number]\r\n"
#define BUFSIZE 128
#define FILENAME "Testfile"

using namespace std;

int main(int argc, char** argv) {
  
  int s = 0;

  if(argc != 2) { 
    cout << USAGE << endl;
    return 1;
  }

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

  for(int x = 0; x <= length / BUFSIZE; x++) {
    string mstr = fstr.substr(x * BUFSIZE, BUFSIZE);

    cout << "x: " << x << endl << mstr << endl << endl;

    if(sendto(s, mstr.c_str(), strlen(mstr.c_str()), 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
      cout << "Package sending failed. (socket s, server address sa, message m)" << endl;
      return 0;
    }

    recvfrom(s, b, BUFSIZE, 0, (struct sockaddr *)&sa, &salen);
    cout << "Response: " << b << endl;
    memset(b, 0, BUFSIZE);
  }

  return 0;
}
