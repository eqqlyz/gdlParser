#include "BasicBlock.h"
#include <string.h>  //使用strtok方法

/*Helper function*/
string trim(char *str){
  // Trim leading non-letters
  while(isspace(*str)) str++;
  // Trim trailing non-letters
  char* end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;
  return string(str, end+1);
}

 /*set the type of the basic block by analyzing the instructions of the basic block*/
 void BasicBlock::setNodeType(){
 
 }


/* Procedure:
 *   1. Separate the string by line
 *   2. If it is label, continue.
 *   3. Separate with ';' to distinguish Asm instruction and annotation
 *   4. Separate the Asm instruction with \t,\s '[' ']' + - etc. Finally get the opcode and oprands of the instruction and store in Asm.
 *   5. Annotate the Asm instruction with annotation.
 *   6. Repeat the above steps until no line exists.
 *
 */

void BasicBlock::getAsmInst(ADDRESS* addr){
  // Lexical analysis of the str_Insts
  // addr needs to be updated whenever an instruction is analyzed.
  char *line, *end_line;
  line = strtok_r((char*)(str_Insts.c_str()),"\n",&end_line);
  while(line){
    //Delete the last return carriage
    if(line[strlen(line)-1] == '\r'){
      line[strlen(line)-1] = '\0';
    }
    // New an assembly instruction
    Asm* pAsm = new Asm();
    // Analysis the instruction
    if(line[strlen(line)-1] == ':'){
      //A Label
      //printf("|%s|\n",line);
      pAsm->setOpcode((char*)(string("label").c_str()));
      pAsm->setOprd1(line);
    }else{
      //Normal instruction
      //printf("{%s}\n",line);
      char *instr, *annot, *end_instrannot;
      instr = strtok_r(line,";",&end_instrannot);
      // Split the instr into opcode and oprands parts
      char *oprds, *opcode, *end_opcodeOprd;
      opcode = strtok_r(instr," ", &end_opcodeOprd);
      pAsm->setOpcode(opcode);
      oprds = strtok_r(NULL, "", &end_opcodeOprd);
      //Split operands
      char *oprd, *end_oprd;
      int oprdNum = 1;
      oprd = strtok_r(oprds,",",&end_oprd);
      while(oprd){
        string tmps = trim(oprd);
        char* oprdx = (char*)(tmps.c_str());
        if(oprdNum == 1){
          //eliminate spaces at the head and the tail
          pAsm->setOprd1(oprdx);
          oprdNum++;
        }else if(oprdNum == 2){
          pAsm->setOprd2(oprdx);
          oprdNum++;
        }else if(oprdNum == 3){
          pAsm->setOprd3(oprdx);
          oprdNum++;
        }else if(oprdNum == 4){
          pAsm->setOprd4(oprdx);
          oprdNum++;
        }else if(oprdNum == 5){
          pAsm->setOprd5(oprdx);
          oprdNum++;
        }
        oprd = strtok_r(NULL,",",&end_oprd);
      }
      annot = strtok_r(NULL,";",&end_instrannot);
      if(annot){
        pAsm->setAnnotation(annot);
      }
    }
    // increase the instruction counter and append instruction
    // 增加指令
    m_Insts.insert(pair<ADDRESS,Asm*>((*addr),pAsm));
    (*addr)++;
    line = strtok_r(NULL,"\n",&end_line);
  }
}

/*Set the type of instructions*/
void BasicBlock::setInstructionType(){
  ASMCFG::iterator it = m_Insts.begin();
  for(; it != m_Insts.end(); it++){
    char* op = (*it).second->opcode;
    int i;
    // 如果要扩展其它指令系统，此处需要修改
    for(i = 0; i < x86Opnum; i++){
      const char* x86op = x86Opcodes[i];
      if(!strcmp(op,x86op)){
        break;
      }
    }
    // judge the instruction type according to i
    if(i >= 0 && i <= 28){
      (*it).second->setInstype(MOVE);
      instVector[MOVE] = instVector[MOVE] + 1;
    }else if( i >= 29 && i <= 50){
      (*it).second->setInstype(ARITH);
      instVector[ARITH] = instVector[ARITH] + 1;      
    }else if(i >= 51 && i <= 64){
      (*it).second->setInstype(LOGIC);
      instVector[LOGIC] = instVector[LOGIC] + 1;      
    }else if(i >= 65 && i <= 122){
      (*it).second->setInstype(TRASFER);
      instVector[TRASFER] = instVector[TRASFER] + 1;      
    }else if(i >= 123 && i <= 130){
      (*it).second->setInstype(PSEUDO);
      instVector[PSEUDO] = instVector[PSEUDO] + 1;      
    }else if(i >= 131 && i <= 137){
      (*it).second->setInstype(BITOP);
      instVector[BITOP] = instVector[BITOP] + 1;      
    }else if(i >= 138 && i <= 154){
      (*it).second->setInstype(SETOP);
      instVector[SETOP] = instVector[SETOP] + 1;     
    }else if(i >= 155 && i <= 181){
      (*it).second->setInstype(REPOP);
      instVector[REPOP] = instVector[REPOP] + 1;     
    }else if(i >= 182 && i <= 251){
      (*it).second->setInstype(FLOAT);
      instVector[FLOAT] = instVector[FLOAT] + 1;      
    }else if(i >= 252 && i <= 298){
      (*it).second->setInstype(XMM);
      instVector[XMM] = instVector[XMM] + 1;      
    }else{
      (*it).second->setInstype(LABELANDFUNCTION);
      instVector[LABELANDFUNCTION] = instVector[LABELANDFUNCTION] + 1;      
    }
  }  
}

/*TEST::Print the instructions in the basic block*/
void BasicBlock::printBB(FILE* f){
  ASMCFG::iterator it = m_Insts.begin();
  for(; it != m_Insts.end(); it++){
    fprintf(f,"0x%x ",(*it).first);
    (*it).second->print(f);
  }
  fprintf(f,"------------\n");
}

/*TEST::undefined opcodes*/
void BasicBlock::undefOpcodes(FILE *f,char* fName){
  ASMCFG::iterator it = m_Insts.begin();
  for(; it != m_Insts.end(); it++){
    char* op = (*it).second->opcode;
    bool found = false;
    for(int i = 0; i < x86Opnum; i++){
      const char* x86op = x86Opcodes[i];
      if(!strcmp(op,x86op)){
        found = true;
        break;
      }
    }
    //输出到文件中
    if(!found){
      //(*it).second->print(f);
      fprintf(f,"%s  ::  %s\n",fName,op);
    }
  }  
}


/*TEST::Print the vector of instruction type*/
void BasicBlock::printInstVector(FILE* f){
  fprintf(f,"[");
  for(int i = 0; i<LABELANDFUNCTION; i++){
    fprintf(f,"%f,",instVector[i]);
  }
  fprintf(f,"]\n");
}


