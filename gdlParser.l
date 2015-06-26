/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb1-4.l,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */

/* recognize tokens for the calculator and print them out */

%{

#include "GDLTreeNode.h"
#include "Cfg.h"

/*定义yylval的类型*/
union {
 int num;
 char* str;
} yylval;

//lexer的接口
void yyerror(char *s, ...);
int curr_lineno = 0;
char* curr_filename = NULL;

//存储整个graph树的根
GDLTreeNode* gdlRoot;
GDLTreeNode *currNode = NULL;
//存储控制流图
Cfg *cfg;

//函数申明
GDLTreeNode* buildGDLTree(char* argv);
void printGDLTree(char* outFile);
Cfg* buildCFG(string inFile);
//控制流分析


%}



%%

"\""              { 
                    int prev,next,idx = 0;
                    char strs[50000];  //程序最大的bug！如果字符串长度过长，会引发段错误
                    prev = yyinput();
                    next = yyinput();
                    // 增加行数
                    if(prev == '\n')
                      curr_lineno++;
			              while(next != EOF){
			                if(next == EOF)
			                  break;
                      if(prev == '\\' && next == '\"'){
                        strs[idx++] = prev;
                      }else if(prev != '\\' && next == '\"'){
                        strs[idx++] = prev;
                        break;
                      }else{
                        strs[idx++] = prev;        
                      }
                      //更新prev和next
                      prev = next;
                      next = yyinput();
			              }
			              //strs[idx++] = '\"';
			              strs[idx] = '\0';
			              //printf("strlen(strs) = %d\n",strlen(strs));
                    //拷贝并回传字符串值
                    yylval.str = strdup(strs);
                    return STR_CONST;
                  }
"//"[^\n]*        {curr_lineno++; /*增加行数*/}
[ \t]+            {}
[0-9]+            { yylval.num = atoi(yytext); return INT_CONST;}
\n                {curr_lineno++; /*增加行数*/}

"graph"           {return GRAPH;}
"title"           {return TITLE;}

"manhattan_edges" {return MANHATTAN_EDGES;}
"layoutalgorithm" {return LAYOUTALGORITHM;}
"finetuning"      {return FINETUNING;}
"layout_downfactor" {return LAYOUT_DOWNFACTOR;}
"layout_upfactor"  {return LAYOUT_UPFACTOR;}
"layout_nearfactor" {return LAYOUT_NEARFACTOR;}
"xlspace"         {return XLSPACE;}
"yspace"          {return YSPACE;}
"colorentry"      {return COLORENTRY;}

"node"            {return NODE;}
"label"           {return LABEL;}
"edge"            {return EDGE;}
"sourcename"      {return SOURCENAME;}
"targetname"      {return TARGETNAME;}
"color"           {return COLOR;}
"vertical_order"  {return VERTICAL_ORDER;}
 
":"               {return COMMA;}
"{"               {return LEFT_PARA;}
"}"               {return RIGHT_PARA;}
[a-z]+            {yylval.str = strdup(yytext);return SYM_VALUE;}

%%
// Main function
main(int argc, char** argv){
  //Store the two cfgs
  Cfg *srcCfg, *dstCfg;
  FILE* fin;
  // Set file as the standard input
  if(argc == 3) {
    if(!(fin = fopen(argv[1], "r"))) {
      printf("Error: can't open file %s\n",argv[1]);
      return (1);
    }else{
      yyrestart(fin);
      //Construct the first CFG
      gdlRoot = buildGDLTree(argv[1]);
      if(gdlRoot == NULL){
        fprintf(stderr,"Incomplete analysis of file %s\n",argv[2]);
        return 1;
      }      
      strcpy(&argv[1][0] + strlen(argv[1]) - 4,"\0");
      srcCfg = buildCFG(argv[1]);
      srcCfg->label2AsmList();
      fclose(fin);
      // Need to clean gdlRoot
    }
    if(!(fin = fopen(argv[2], "r"))){
      printf("Error: can't open file %s\n",argv[2]);
      return (1);      
    }else{
      yyrestart(fin);
      //Construct the second CFG
      gdlRoot = NULL;
      gdlRoot = buildGDLTree(argv[2]);
      if(gdlRoot == NULL){
        fprintf(stderr,"Incomplete analysis of file %s\n",argv[2]);
        return 1;
      }
      strcpy(&argv[2][0] + strlen(argv[2]) - 4,"\0");
      dstCfg = buildCFG(argv[2]);
      dstCfg->label2AsmList();
      fclose(fin);
      // Need to clean gdlRoot
    }
  }
  //TEST PART
  // 1. Test the parser
  /*fin = fopen("test.out","a");
  srcCfg->printCFG(fin);
  fclose(fin);*/
  // 2. Test the instruction set
  /*fin = fopen("undef.txt","a");
  srcCfg->undefOpcodes(fin,argv[1]);
  fclose(fin);*/
  // 2. Test the instruction vector
  /*srcCfg->setInstructionType();
  fin = fopen("undef.txt","a");
  srcCfg->printInstVector(fin,argv[1]);
  fclose(fin);*/
  // Start the similarity calculation.
}

/* bug:: 由于对某些模式分析的不是非常到位，因此，需要不断的完善buildGDLTree方法
*/

GDLTreeNode* buildGDLTree(char* argv){
  int tok;
  //初始化curr_lineno和curr_filename
  curr_lineno = 0;
  curr_filename = argv;
  GDLTreeNode* gdlRoot;
  //开始遍历整个文件
  while(tok = yylex()) {
    /*分别对待*/
    switch(tok){
      case GRAPH:
        gdlRoot = new GDLTreeNode(GRAPH_N);
        gdlRoot->setParent(NULL);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename , curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != LEFT_PARA){
          printf("File '%s' : Without '{' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }        
        break;
      case TITLE:
        currNode = new GDLTreeNode(TITLE_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != STR_CONST){
          printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置title值
        currNode->setTitle(string(yylval.str));
        break;
      case MANHATTAN_EDGES:
        currNode = new GDLTreeNode(MANHATTAN_EDGES_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != SYM_VALUE){
          printf("File '%s' : Not a symbol at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置manhattan_edges值
        currNode->setManhattan_edges(string(yylval.str));        
        break;
      case LAYOUTALGORITHM:
        currNode = new GDLTreeNode(LAYOUTALGORITHM_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != SYM_VALUE){
          printf("File '%s' : Not a symbol at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置layoutalgorithm值
        currNode->setLayoutalgorithm(string(yylval.str));        
        break;
      case FINETUNING:
        currNode = new GDLTreeNode(FINETUNING_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != SYM_VALUE){
          printf("File '%s' : Not a symbol at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置finetuning值
        currNode->setFinetuning(string(yylval.str));        
        break;
      case LAYOUT_DOWNFACTOR:
        currNode = new GDLTreeNode(LAYOUT_DOWNFACTOR_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置layout_downfactor值
        currNode->setLayout_downfactor(yylval.num);        
        break;
      case LAYOUT_UPFACTOR:
        currNode = new GDLTreeNode(LAYOUT_UPFACTOR_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置layout_upfactor值
        currNode->setLayout_upfactor(yylval.num);         
        break;
      case LAYOUT_NEARFACTOR:
        currNode = new GDLTreeNode(LAYOUT_NEARFACTOR_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置layout_upfactor值
        currNode->setLayout_nearfactor(yylval.num);          
        break;
      case XLSPACE:
        currNode = new GDLTreeNode(XLSPACE_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置xlspace值
        currNode->setXlspace(yylval.num);          
        break;
      case YSPACE:
        currNode = new GDLTreeNode(YSPACE_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        //设置yspace值
        currNode->setYspace(yylval.num);         
        break;
      case COLORENTRY:
        currNode = new GDLTreeNode(COLORENTRY_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        //设置颜色编号
        currNode->setColorentry(yylval.num);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }  
        int r,g,b;      
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        r = yylval.num;
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        g = yylval.num;
        tok = yylex();
        if(tok != INT_CONST){
          printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
          return NULL;        
        }
        b = yylval.num;                
        //设置colorentry的(r,g,b)值
        currNode->setRgb_Color(r,g,b);
        break;
      case NODE:
        currNode = new GDLTreeNode(NODE_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != LEFT_PARA){
          printf("File '%s' : Without '{' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != TITLE){
          printf("File '%s' : Without title at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }        
        tok = yylex();
        if(tok != STR_CONST){
          printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        //设置title和rank
        currNode->setTitle(string(yylval.str));
        currNode->setRank(string(yylval.str));
        tok = yylex();
        if(tok != LABEL){
          printf("File '%s' : Without label at line %d\n",curr_filename,curr_lineno);
          return NULL;
        } 
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }               
        tok = yylex();
        if(tok != STR_CONST){
          printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        //设置label
        currNode->setLabel(string(yylval.str));
        tok = yylex();
        if(tok == RIGHT_PARA){
          break;
        }else if(tok == VERTICAL_ORDER){
          tok = yylex();
          if(tok != COMMA){
            printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
            return NULL;
          }
          tok = yylex();
          if(tok != INT_CONST){
            printf("File '%s' : Not an int at line %d\n",curr_filename,curr_lineno);
            return NULL;
          }   
          //设置vertical_order
          currNode->setVertical_order(yylval.num);   
          tok = yylex();
          if(tok != RIGHT_PARA){
            printf("File '%s' : Without '}' at line %d\n",curr_filename,curr_lineno);
            return NULL;
          }                        
        }else if(tok == COLOR){
          tok = yylex();
          if(tok != COMMA){
            printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
            return NULL;
          }
          tok = yylex();
          if(tok != SYM_VALUE){
            printf("File '%s' : Not a symbol at line %d\n",curr_filename,curr_lineno);
            return NULL;
          }            
          //设置color值
          currNode->setNodeColor(string(yylval.str));        
        }else{
          printf("File '%s' : Without '}' at line %d\n",curr_filename,curr_lineno);
          return NULL;         
        }
        break;
      case EDGE:
        currNode = new GDLTreeNode(EDGE_N);
        currNode->setParent(gdlRoot);
        gdlRoot->insertChild(currNode);
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != LEFT_PARA){
          printf("File '%s' : Without '{' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }
        tok = yylex();
        if(tok != SOURCENAME){
          printf("File '%s' : Not SOURCENAME at line %d\n",curr_filename,curr_lineno);
          return NULL;
        } 
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }                  
        tok = yylex();
        if(tok != STR_CONST){
          printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }          
        //设置sourcename
        currNode->setSourcename(string(yylval.str));
        tok = yylex();
        if(tok != TARGETNAME){
          printf("File '%s' : Not TARGETNAME at line %d\n",curr_filename,curr_lineno);
          return NULL;
        } 
        tok = yylex();
        if(tok != COMMA){
          printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }                  
        tok = yylex();
        if(tok != STR_CONST){
          printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
          return NULL;
        }          
        //设置sourcename
        currNode->setTargetname(string(yylval.str)); 
        tok = yylex();
        if(tok == RIGHT_PARA){
          break;
        }else{
          //说明还有label和color属性
         //tok = yylex();
         if(tok != LABEL){
           printf("File '%s' : Not a label at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }
         tok = yylex();
         if(tok != COMMA){
           printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }
         tok = yylex();
         if(tok != STR_CONST){
           printf("File '%s' : Not a string at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }            
         //设置label值
         currNode->setLabel(string(yylval.str));
         tok = yylex();
         if(tok != COLOR){
           printf("File '%s' : Not a color at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }
         tok = yylex();
         if(tok != COMMA){
           printf("File '%s' : Without ':' at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }
         tok = yylex();
         if(tok != SYM_VALUE){
           printf("File '%s' : Not a symbol at line %d\n",curr_filename,curr_lineno);
           return NULL;
         }            
         //设置color值
         currNode->setEdgeColor(string(yylval.str));       
        }           
        break;
      default:
        break;
    } // end of switch
  } // end of while
  // return the Tree Root
  return gdlRoot;
}

void printGDLTree(char* outFile){
  FILE *f = fopen(outFile,"w");
  fprintf(f,"digraph G{\n");
  for(int i = 0; i < gdlRoot->getChildrenNum(); i++){
    currNode = gdlRoot->getNthChild(i);
    if(currNode != NULL){
      GDLTREENODETYPE nodeType = currNode->getNodeType();
      if(nodeType == NODE_N){
        fprintf(f,"Node%d [label = \"%s\"]\n",currNode->getRank(),currNode->getLabel().c_str());
      }else if(nodeType == EDGE_N){
        if(currNode->getEdgeColor() == RED){
          fprintf(f,"Node%d -> Node%d [color = \"red\"]\n",currNode->getSourcename(),currNode->getTargetname());
        }else if(currNode->getEdgeColor() == DARKGREEN){
          fprintf(f,"Node%d -> Node%d [color = \"green\"]\n",currNode->getSourcename(),currNode->getTargetname());
        }else{
          fprintf(f,"Node%d -> Node%d [color = \"black\"]\n",currNode->getSourcename(),currNode->getTargetname());
        }
      }
    }
  }
  //Close the file
  fprintf(f,"}");
  fclose(f);
}

Cfg* buildCFG(string inFile){
  Cfg* cfgx = new Cfg(inFile);
  for(int i = 0; i < gdlRoot->getChildrenNum(); i++){
    currNode = gdlRoot->getNthChild(i);
    if(currNode != NULL){
      GDLTREENODETYPE nodeType = currNode->getNodeType();
      if(nodeType == NODE_N){
        //Construct Basic Block
        cfgx->insertBB(currNode->getRank(),currNode->getLabel());
      }else if(nodeType == EDGE_N){
        //Insert an edge
        cfgx->insertEdge(currNode->getSourcename(),currNode->getTargetname());
        if(currNode->getEdgeColor() == RED){
          //false part      
        }else if(currNode->getEdgeColor() == DARKGREEN){
          //true part
        }else{
          //a normal one
        }
      }
    }
  }
  return cfgx;  
}
