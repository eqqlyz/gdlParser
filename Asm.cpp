#include "Asm.h"


/*set{opcode,oprd1,oprd2,oprd3}*/
void Asm::setOpcode(char* opcode){
  if(opcode != NULL){
	  this->opcode = new char[strlen(opcode)+1];
    strcpy(this->opcode,opcode);
  }else{this->opcode =NULL;}	
}

void Asm::setOprd1(char* oprd1){
  if(oprd1 != NULL){
    this->oprd1 = new char[strlen(oprd1)+1];
    strcpy(this->oprd1,oprd1);
    oprdNum ++;		//oprdNum + 1
  }else{this->oprd1 =NULL;}	
}

void Asm::setOprd2(char* oprd2){
  if(oprd2 != NULL){
    this->oprd2 = new char[strlen(oprd2)+1];
    strcpy(this->oprd2,oprd2);
    oprdNum ++;		//oprdNum + 1
  }else{this->oprd2 =NULL;}	
}

void Asm::setOprd3(char* oprd3){
  if(oprd3 != NULL){
    this->oprd3 = new char[strlen(oprd3)+1];
    strcpy(this->oprd3,oprd3);
    oprdNum ++;		//oprdNum + 1
	}else{this->oprd3 =NULL;}	
}
/*set{oprd4,oprd5}*/
void Asm::setOprd4(char* oprd4){
  if(oprd4 != NULL){
    oprdNum++;			//oprdNum + 1
    this->oprd4 = new char[strlen(oprd4)+1];
    strcpy(this->oprd4,oprd4);
  }else{this->oprd4 =NULL;}	
}

void Asm::setOprd5(char* oprd5){
  if(oprd5 != NULL){
	  oprdNum++;			//oprdNum + 1
	  this->oprd5 = new char[strlen(oprd5)+1];
	  strcpy(this->oprd5,oprd5);
	}else{this->oprd5 =NULL;}	
}

/*set {Annotation}*/
void Asm::setAnnotation(char* annot){
  if(annot != NULL){
    this->annotation = new char[strlen(annot)+1];
    strcpy(this->annotation,annot);
  }else{this->oprd5 =NULL;}	
}

/*set the instruction type*/
void Asm::setInstype(INST_TYPE type){
  instType = type;
}

/*print the instruction*/
void Asm::print(FILE *f){
  if(opcode!=NULL)
    fprintf(f,"|%s| ",opcode);
  if(oprd1!=NULL)
    fprintf(f,"|%s|,",oprd1);
  if(oprd2!=NULL)
    fprintf(f,"|%s|,",oprd2);
  if(oprd3!=NULL)
    fprintf(f,"|%s|,",oprd3);
  if(oprd4!=NULL)
    fprintf(f,"|%s|,",oprd4);
  if(oprd5!=NULL)
    fprintf(f,"|%s|,",oprd5);
  fprintf(f,"\n");
}
