
#include<stack>
#include"Cfg.h"

/*Insert a basic block according to its rank*/
void Cfg::insertBB(int rank,string lab){
  PBB cBB = new BasicBlock(rank);
  cBB->set_Str_Insts(lab);
  m_listBB.push_back(cBB);
}
/*Insert an edge*/
void Cfg::insertEdge(unsigned int srcBB,unsigned int dstBB){
  //1. Find the basic block with the specified basic block number
  list<PBB>::iterator it = m_listBB.begin();
  PBB fBB, tBB;
  for(;it!=m_listBB.end();it++){
    if(srcBB == (*it)->getRank()){
      fBB = (*it);
    }
    if(dstBB == (*it)->getRank()){
      tBB = (*it);
    }
  }
  //2. Add the bidirected edge
  fBB->appendOutEdge(tBB);
  tBB->appendInEdge(fBB);
}
/*Analysis the string of the instruction list*/
void Cfg::label2AsmList(){
  list<PBB>::iterator it = m_listBB.begin();
  ADDRESS instNum = 0;
  for(;it != m_listBB.end();it++){
    (*it)->getAsmInst(&instNum);
  }
}

/*Set the type of instructions*/
void Cfg::setInstructionType(){
  list<PBB>::iterator it = m_listBB.begin();
  for(;it != m_listBB.end();it++){
    (*it)->setInstructionType();
  }
}

/*TEST::Print the assembly program into file*/
void Cfg::printCFG(FILE* f){
  list<PBB>::iterator it = m_listBB.begin();
  for(;it != m_listBB.end();it++){
    (*it)->printBB(f);
  }  
}

/*TEST::Stat undefined opcodes*/
void Cfg::undefOpcodes(FILE* f,char* fName){
  list<PBB>::iterator it = m_listBB.begin();
  for(;it != m_listBB.end();it++){
    (*it)->undefOpcodes(f,fName);
  }  
}

/*TEST::Print the vector of instruction type*/
void Cfg::printInstVector(FILE* f, char* fName){
  fprintf(f, "Func::  %s\n",fName);
  list<PBB>::iterator it = m_listBB.begin();
  for(;it != m_listBB.end();it++){
    (*it)->printInstVector(f);
  }    
  fprintf(f,"----------\n");
}


