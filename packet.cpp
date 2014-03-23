
class Packet{
  //Public functions and variables
  public:
    void setSequenceNum(int sn);
    void setCheckSum(int cs);
    void setAckNack(int an);
    int getSequenceNum();
    int getCheckSum();
    int getAckNack();
    void loadDataBuffer(String data);
    String getDataBuffer();
    Packet(); //constructor
  };
  //Private variables
  private:
    int sequenceNum;
    int checkSum;
    int ackNack;
    char dataBuff[126];
  };
  //Constructor
  Packet::Packet(void){

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
