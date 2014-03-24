#include "packet.h"
#include <string.h>

  //Constructor
  Packet::Packet () {
	sequenceNum = 0;
	checkSum = 0;
	ackNack = 0;
  }
  Packet::Packet (int sn, const char db[126]){
    sequenceNum = (sn + 1) % 2;
    strcpy(dataBuff, db);
    checkSum = 0;
    ackNack =0;
  }
  //Setter Methods
  void Packet::setSequenceNum(int sn){
     sequenceNum = sn;
  }
 
  void Packet::setCheckSum(int cs){
     checkSum = cs;
  }
 
  void Packet::setAckNack(int an){
     ackNack = an;
  }

  void Packet::loadDataBuffer(char* data){
    //Jakes load buffer code goes here
  }
  char* Packet::getDataBuffer() {
    return dataBuff;
  }
  //Attach header to the data array
  char* Packet::str(char* data){
    std::string tempStr(data);
    std::string packetString;
    packetString = std::to_string(sequenceNum) + std::to_string(checkSum) + std::to_string(ackNack) + tempStr;
    std::strcpy(packet, packetString.c_str());
    return packet;
  }
  //Getter Methods
  int Packet::getSequenceNum(){
    return sequenceNum;
  }
 
  int Packet::getCheckSum(){
    return checkSum;
  }

  int Packet::getAckNack(){
    return ackNack;
  }
  bool Packet::chksm() {
    return (checkSum) == generateCheckSum();
  }
  int Packet::generateCheckSum() {
    int cs = 0;
    if(dataBuff == NULL){
      return -1;
    }

    for(int x = 0; x < sizeof(dataBuff); x++) {
      cs += dataBuff[x];
    }

    if(cs > 0) return cs;
    return -1;
  }
