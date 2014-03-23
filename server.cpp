#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "packet.h"

#define PORT 10038
#define BUFSIZE 128
#define ACK "ACK"
#define NAK "NAK"

using namespace std;

bool isvpack() {
  // change to validate based on checksum and sequence number
  return true;
}

int main() {
  struct sockaddr_in a;
  struct sockaddr_in ca;
  socklen_t calen = sizeof(ca);
  int rlen;
  int s;
  string ack;
  bool seqNum = true;

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
    Packet * p;
    cout << "Base packet formed." << endl;
    rlen = recvfrom(s, p, 2 * BUFSIZE, 0, (struct sockaddr *)&ca, &calen);
    cout << "Received " << rlen << " bytes." << endl;
    if (rlen > 0) {
      cout << "Received message: " << endl << p->getDataBuffer() << endl;
      if(isvpack()) {
        ack = "ACK";
        file << p->getDataBuffer();
      } else { 
        ack = "NAK";
      }
      if(sendto(s, ack.c_str(), strlen(ack.c_str()), 0, (struct sockaddr *)&ca, calen) < 0) {
        cout << "Acknowledgement failed. (socket s, acknowledgement message ack, client address ca, client address length calen)" << endl;
        return 0;
      }
    }
  }
}
