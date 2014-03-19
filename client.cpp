#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  
  int s = 0;

  string hs = "54.186.88.157"; /* Needs to be updated? Might be a string like "tux175.engr.auburn.edu." */
  short int port = 10038; /* Can be any port within 10038-10041, inclusive. */

  struct sockaddr_in a;
  struct sockaddr_in sa;
  struct hostent *h;

  string m = "Hello, server world!";

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
  inet_aton(hs.c_str(), &sa.sin_addr);

  cout << "Server address: " << inet_ntoa(sa.sin_addr) << endl;
  cout << "Port: " << ntohs(sa.sin_port) << endl;
  cout << "Client address: " << ntohl(a.sin_addr.s_addr) << endl;
  cout << "Port: " << ntohs(a.sin_port) << endl;

  if(sendto(s, m.c_str(), strlen(m.c_str()), 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
    perror("Package sending failed. (socket s, server address sa, message m)");
    return 0;
  }

  return 0;
}
