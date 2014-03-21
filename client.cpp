#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#define USAGE "Usage:\r\nc [tux machine number]\r\n"

using namespace std;

int main(int argc, char** argv) {
  
  int s = 0;
  
  //if argv[1] doesn't exist
  //    print the usage string

  cout << USAGE << endl;

  string hs = string("131.204.14.") + argv[1]; /* Needs to be updated? Might be a string like "tux175.engr.auburn.edu." */
  short int port = 10038; /* Can be any port within 10038-10041, inclusive. */

  struct sockaddr_in a;
  struct sockaddr_in sa;
  struct hostent *h;

  string m = "Hello, server world!";

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
  //if(inet_aton(hs.c_str(), &sa.sin_addr) == 0) {
    //cout << "Server address conversion failed. (host string hs, server address sa)" << endl;
    //return 0;
  //}

  cout << endl;

  cout << "Server address (inet mode): " << inet_ntoa(sa.sin_addr) << endl;
  cout << "Port: " << ntohs(sa.sin_port) << endl;

  cout << endl;

  cout << "Message: " << m << endl;

  cout << endl;

  if(sendto(s, m.c_str(), strlen(m.c_str()), 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
    cout << "Package sending failed. (socket s, server address sa, message m)" << endl;
    return 0;
  }

  return 0;
}
