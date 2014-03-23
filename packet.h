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
    void loadDataBuffer(std::string data);
    std::string getDataBuffer();
    Packet(int sn, char db[126]);
    Packet(); //constructor
};
