#ifndef GDLTREENODE_H
#define GDLTREENODE_H

#include<vector>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

/*一些宏定义*/
#define GRAPH 258
#define TITLE 259 
#define MANHATTAN_EDGES 260 
#define LAYOUTALGORITHM 261
#define FINETUNING 262 
#define LAYOUT_DOWNFACTOR 263
#define LAYOUT_UPFACTOR 264
#define LAYOUT_NEARFACTOR 265
#define XLSPACE 266
#define YSPACE 267
#define COLORENTRY 268
#define NODE 269
#define LABEL 270
#define EDGE 271 
#define SOURCENAME 272
#define TARGETNAME 273
#define COLOR 274
#define SYM_VALUE 275
#define COMMA 276 
#define LEFT_PARA 277
#define RIGHT_PARA 278
#define VERTICAL_ORDER 279
#define STR_CONST 280
#define INT_CONST 281

/**/ 
enum GDLTREENODETYPE{
  GRAPH_N = 1,
  TITLE_N,
  MANHATTAN_EDGES_N,
  LAYOUTALGORITHM_N,
  FINETUNING_N,
  LAYOUT_DOWNFACTOR_N,
  LAYOUT_UPFACTOR_N,
  LAYOUT_NEARFACTOR_N,
  XLSPACE_N,
  YSPACE_N,
  COLORENTRY_N,
  NODE_N,
  LABEL_N,
  EDGE_N,
  SOURCENAME_N,
  TARGETNAME_N,
  COLOR_N,
  OTHERS
};

//
enum EDGECOLOR{
	RED = 1,
	DARKGREEN,
	BLACK
};

// 
struct rgbColor{
  int rColor;
  int gColor;
  int bColor;
};


/*Only node type*/
class GDLTreeNode{
public:
	GDLTreeNode(GDLTREENODETYPE nt){ 
		nodeType = nt; 
		children.empty();
		parent = NULL;
		colorentry = -1;
		edgeColor = BLACK;
		finetuning.empty();
		label.empty();
		layoutalgorithm.empty();
		layout_downfactor = -1;
		layout_nearfactor = -1;
		layout_upfactor = -1;
		manhattan_edges.empty();
		rank = -1;
		sourcename = -1;
		targetname = -1;
		title.empty();
		xlspace = -1;
		yspace = -1;
	}
	~GDLTreeNode(){}
	/**/
	void setNodeType(GDLTREENODETYPE nt){ nodeType = nt; }
	/**/
	GDLTREENODETYPE getNodeType(){ return nodeType;}
	/**/
	void setParent(GDLTreeNode* tn){ parent = tn;}
	/**/
	GDLTreeNode* getParent(){ return parent; }
	/**/
	void insertChild(GDLTreeNode* tn){
		if(tn != NULL)
   		  children.push_back(tn);
	}
	/**/
	int getChildrenNum(){ return children.size(); }
	/**/
	GDLTreeNode* getNthChild(unsigned int n){
		if(n >=0 && n < children.size())
			return children[n];
		return NULL;
	}
	/**/
	void setTitle(string tmp){ title  = tmp;	 }
	/**/
	string getTitle(){  return title;}
	/**/
	void setRank(string tmp){ rank  = stoi(tmp);	 }
	/**/
	unsigned int getRank(){  return rank;}
	/**/
	void setLabel(string tmp){ label  = tmp;	}
	/**/
	string getLabel(){  return label;}
	/**/
	void setManhattan_edges(string me){ manhattan_edges = me;}
	/*manhattan_edges*/
	string getManhattan_edges(){return manhattan_edges;}
	/*layoutalgorithm*/
	void setLayoutalgorithm(string la){ layoutalgorithm = la;}
	/*layoutalgorithm*/
	string getLayoutalgorithm(){return layoutalgorithm;}
	/*finetuning*/
	void setFinetuning(string ft){ finetuning = ft;}
	/*finetuning*/
	string getFinetuning(){ return finetuning;}
	/*layout_downfactor*/
	void setLayout_downfactor(int ld){ layout_downfactor = ld;}
	/*layout_downfactor*/
	int getLayout_downfactor(){return layout_downfactor;}
	/*layout_upfactor*/
	void setLayout_upfactor(int ld){ layout_upfactor = ld;}
	/*layout_upfactor*/
	int getLayout_upfactor(){return layout_upfactor;}	
	/*layout_nearfactor*/
	void setLayout_nearfactor(int ld){ layout_nearfactor = ld;}
	/*layout_nearfactor*/
	int getLayout_nearfactor(){return layout_nearfactor;}	
	/*xlspace*/
	void setXlspace(int ld){ xlspace = ld;}
	/*xlspace*/
	int getXlspace(){return xlspace;}	
	/*yspace*/
	void setYspace(int ld){ yspace = ld;}
	/*yspace*/
	int getYspace(){return yspace;}	
	/*colorentry*/
	void setColorentry(int ld){ colorentry = ld;}
	/*colorentry*/
	int getColorentry(){return colorentry;}	
	/*rgb_Color*/
	void setRgb_Color(int r, int g, int b){ 
		rgb_Color.rColor = r;
		rgb_Color.gColor = g;
		rgb_Color.bColor = b;
	}
	/*rgb_Color*/
	struct rgbColor getRgb_Color(){return rgb_Color;}	
	/*sourcename*/
	void setSourcename(string la){ sourcename = stoi(la);}
	/*sourcename*/
	int getSourcename(){return sourcename;}
	/*targetname*/
	void setTargetname(string la){ targetname = stoi(la);}
	/*targetname*/
	int getTargetname(){return targetname;}
	/*edgeColor*/
	void setEdgeColor(string la){ 
		if(la == "red"){
		  edgeColor = RED;
		}else if(la == "darkgreen"){
		  edgeColor = DARKGREEN;
		}else{
		  edgeColor = BLACK;
		}
	}
	/*edgeColor*/
	EDGECOLOR getEdgeColor(){return edgeColor;}
	/*vertical order*/
	void setVertical_order(int ld){ vertical_order = ld;}
	int getVertical_order(){ return vertical_order;}	
	
	
private:
	/**/
	GDLTREENODETYPE nodeType;
	/**/
	GDLTreeNode* parent;
	/**/
	vector<GDLTreeNode*> children;
	/*-------------*/
	/**/
	string title;
	/**/
	unsigned int rank;
	/*label*/
	string label;
	/*manhattan_edges*/
	string manhattan_edges;
	/*layoutalgorithm*/
	string layoutalgorithm;
	/*finetuning*/
	string finetuning;
	/*layout_downfactor*/
	int layout_downfactor;
	/*layout_upfactor*/
	int layout_upfactor;
	/*layout_nearfactor*/
	int layout_nearfactor;
	/*xlspace*/
	int xlspace;
	/*yspace*/
	int yspace;
	/**/
	int colorentry;
	/**/
  struct rgbColor  rgb_Color;
  /**/
  int vertical_order;
	/*targetname*/
	int sourcename;
	int targetname;
	/**/
	EDGECOLOR edgeColor;
	/*------------*/
};


#endif
