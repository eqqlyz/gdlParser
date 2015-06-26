#ifndef ASM_H
#define ASM_H

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"Opcodes.h"

// instruction set type
enum MACHINE_TYPE{
  X86_MACHINE = 1,
  PPC_MACHINE,
  MIPS_MACHINE
};


/*Instruction class*/
enum INST_TYPE{
  MOVE = 0,
  ARITH,
  LOGIC,
  TRASFER,
  PSEUDO,
  BITOP,
  SETOP,
  REPOP,
  FLOAT,
  XMM,
  LABELANDFUNCTION
};

/*
 * class to store assembly instruction
 */
class Asm{
public:
	Asm(){
		/*opcode*/
		oprdNum = 0;			//operand number
		opcode = oprd1 = oprd2 = oprd3 = oprd4 = oprd5 = NULL;
	}
	/*ÊôÐÔ¶Î*/
	char* opcode;		  //opcode
	int oprdNum;		  //number of operand
	char* oprd1;			//first operand
	char* oprd2;			//second operand
	char* oprd3;			//third operand
	char* oprd4;			//fourth operand
	char* oprd5;			//fifth operand
	char* annotation;  //annotation
	INST_TYPE instType; // Instruction Type

	/*set{opcode,oprd1,oprd2,oprd3}*/
	void setOpcode(char* opcode);
	void setOprd1(char* oprd1);
	void setOprd2(char* oprd2);
	void setOprd3(char* oprd3);
	/*set{oprd4,oprd5}*/
	void setOprd4(char* oprd4);
	void setOprd5(char* oprd5);
  /*set annotation*/
	void setAnnotation(char* annot);
	/*set the instruction type*/
	void setInstype(INST_TYPE type);
	/*print the instruction*/
	void print(FILE *f);
};

#endif    //ASM_H
