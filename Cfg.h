#ifndef CFG_H
#define CFG_H

#include<list>
#include<string>
#include"BasicBlock.h"


class Cfg{
public:
  /*Constructor using the function name*/
  Cfg(string fName){
    m_listBB.clear();
    funcName = fName;
  }
  /*Destructor*/
  ~Cfg();
  /*Insert a basic block according to its rank*/
  void insertBB(int rank,string lab);
  /*Insert an edge*/
  void insertEdge(unsigned int srcBB,unsigned int dstBB);
  /*Analysis the string of the instruction list*/
  void label2AsmList();
  /*Get the size of the cfg*/
  int getSize(){ return m_listBB.size();}
  /*Set the type of instructions*/
  void setInstructionType();
  /*TEST::Test the label2AsmList function*/
  void printCFG(FILE* f);
  /*TEST::Stat undefined opcodes*/
  void undefOpcodes(FILE* f, char* fName);
  /*TEST::Print the vector of instruction type*/
  void printInstVector(FILE* f, char* fName);
private:
  /*Store the basic blocks of a procedure in a list*/
  list<PBB> m_listBB;
  /*Function name*/
  string funcName;
};


#endif   //CFG_H
