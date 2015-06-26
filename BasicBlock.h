#ifndef BASICBLOCK_H
#define BASICBLOCK_H


#include<vector>
#include<map>
#include<string>
#include"Asm.h"

using namespace std;

class BasicBlock;
typedef unsigned int ADDRESS;
typedef BasicBlock* PBB;
typedef map<ADDRESS,Asm*, less<ADDRESS> > ASMCFG;

// Basic Block type
enum BBTYPE{
  ONEWAY,					// unconditional branch
  TWOWAY,					// conditional branch
  NWAY,						// case branch
  CALL,						// procedure call
  RET,						// return
  FALL,						// fall-through node
  COMPJUMP,				// computed jump
  COMPCALL,				// computed call
  INVALID					// invalid instruction
};


class BasicBlock{
public:
  /*Constructor*/
  BasicBlock(int rank){
    // Initiate the basic block.
    bb_rank = rank;
    m_InEdges.clear();
    m_OutEdges.clear();
    m_nodeType = INVALID;
    m_Insts.clear();
    instVector = new float[LABELANDFUNCTION+1];  //use the definition in Asm.h
    memset(instVector, (LABELANDFUNCTION + 1)*sizeof(float), 0);
  }
  /*Destructor*/
  ~BasicBlock();
  /*add an in edge*/
  void appendInEdge(PBB nBB){ m_InEdges.push_back(nBB);}
  /*add an out edge*/
  void appendOutEdge(PBB nBB){ m_OutEdges.push_back(nBB);}
  /*Set the str_Insts*/
  void set_Str_Insts(string str){ str_Insts = str;}
  /*set the type of the basic block by analyzing the instructions of the basic block*/
  void setNodeType();
  /*Analysis the instruction string and insert them into the m_Insts map*/
  /*PARAMETER addr is the start address of the basic block*/
  void getAsmInst(ADDRESS* addr);
  /*Set the type of instructions*/
  void setInstructionType();
  /*Get the rank of the current basic block*/
  int getRank(){ return bb_rank;}
  /*TEST::Print the assembly instruction in a basic block*/
  void printBB(FILE* f);
  /*TEST::undefined opcodes*/
  void undefOpcodes(FILE *f,char* fName);
  /*TEST::Print the vector of instruction type*/
  void printInstVector(FILE* f);  
private:
  vector<PBB> m_InEdges;	// In edges
  vector<PBB> m_OutEdges; // Out edges
  BBTYPE m_nodeType;		  // Type of the node
  string str_Insts;       // Instructions in string format
  ASMCFG m_Insts;         // Store the instructions
  int bb_rank;            // The ID of a basic block
  float *instVector;      // Statis the probability of the basic block
};


#endif  //BASICBLOCK_H
