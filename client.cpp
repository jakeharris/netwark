#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  
  int s = 0;

  string hs = "131.204.254.100"; /* Needs to be updated? Might be a string like "tux175.engr.auburn.edu." */
  short int port = 10038; /* Can be any port within 10038-10041, inclusive. */

  struct sockaddr_in a;
  struct sockaddr_in sa;
  struct hostent *h;



  if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    cout << "Socket creation failed. (socket s)" << endl;
    return 0;
  }

  memset((char *)&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = htons(0);

  if (bind(s, (struct sockaddr *)&a, sizeof(a)) < 0){
    cout << "Socket binding failed. (socket s, address a)" << endl;
    return 0;
  }

  memset((char *)&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  memcpy((void *)&sa.sin_addr, hs.c_str(), strlen(hs.c_str()));

  cout << "Server address: " << sa.sin_addr.s_addr << endl;
  cout << "Port: " << ntohs(sa.sin_port) << endl;
  cout << "Client address: " << ntohl(a.sin_addr.s_addr) << endl;
  cout << "Port: " << ntohs(a.sin_port) << endl;

  return 0;
}
