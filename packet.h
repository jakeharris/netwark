#ifndef PACKET_H
#define PACKET_H
#include <stdio.h>
#include <string.h>
#include <iostream>
class Packet{
  //Private variables
  private:
    int sequenceNum;
    int checkSum;
    int ackNack;
    char dataBuff[126];
    std::string tempStr;
    std::string packetString;
    char packet[128];
  //Public functions and variables
  public:
    void setSequenceNum(int sn);
    void setCheckSum(int cs);
    void setAckNack(int an);
    int getSequenceNum();
    int getCheckSum();
    int getAckNack();
    void loadDataBuffer(char* data);
    char* getDataBuffer();
    Packet(int sn, const char db[126]);
    Packet(); //constructor
    char* str(char* data);
};
#endif
