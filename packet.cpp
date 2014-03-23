#include "packet.h"
#include <string.h>
  //Constructor
  Packet::Packet () {

  }
  Packet::Packet (int sn, const char db[126]){
    sequenceNum = (sn + 1) % 2;
    strcpy(dataBuff, db);
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

