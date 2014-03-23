#ifndef PACKET_H
#define PACKET_H

class Packet{
  //Private variables
  private:
    int sequenceNum;
    int checkSum;
    int ackNack;
    char dataBuff[126];
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
};
#endif
