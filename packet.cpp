#include "packet.h"

class Packet {

  //Constructor
  Packet::Packet () {

  }
  Packet::Packet (int sn, char db[126]){
    sequenceNum = (sn + 1) % 2;
    dataBuff = db;
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

  void Packet::loadDataBuffer(String data){
    //Jakes load buffer code goes here
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
};

