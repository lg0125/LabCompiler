#ifndef PARSER_H
#define PARSER_H

#include "ScannerImp.h"

typedef struct tNode{
	int num;
	char element[20];
	struct tNode *child[20];
}tNode;

tNode *tProgram;
tNode *tPoint;
tNode *tSubProgram;

node *p;

int init(tNode **q,char *element);

int initNum(tNode **q,char *element,int childNum);

int printNode(tNode *q);

int program();

int subProgram(tNode **tSubProgramm);


//1
int constDef(tNode **tConstDef);

int unsignedInt(tNode **tUnsignedInt);

int id(tNode **tId);

//1
int conExplain(tNode **tConExplain);

//2
int varExplain(tNode **tVarExplain);

//3
int processHead(tNode **tProcessHead);

int processExplain(tNode **tProcessExplain);

//4
int statement(tNode **tStatement);

//4.1
int mulDivide(tNode **tMulDivide);

int factor(tNode **tFactor);

int addSubtract(tNode **tAddSubtract);

int item(tNode **tItem);

int expression(tNode **tExpression);

int assignmentStatement(tNode **tAssignmentStatement);

//4.2
int relationship(tNode **tRelationship);

int conditions(tNode **tConditions);

int conditionStatement(tNode **tConditionStatement);

//4.3
int doWhile(tNode **tDoWhile);

//4.4
int processCall(tNode **tProcessCall);

//4.5
int readStatement(tNode **tReadStatement);

//4.6
int writeStatement(tNode **tWriteStatement);

//4.7
int compoundStatement(tNode **tCompoundStatement);

void print(tNode *root,int num);

#endif
