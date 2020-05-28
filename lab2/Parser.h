#ifndef PARSER_H
#define PARSER_H

#include "ScannerImp.h"

node *p;

int subProgram();

int conExplain();

int varExplain();

int processExplain();

int constDef();

int statement();

int id();

int unsignedInt();

int digit();

int processHead();

int assignmentStatement();

int expression();

int compoundStatement();

int conditions();

int addSubstract();

int item();

int factor();

int mulDivide();

int conditionStatement();

int relationship();

int processCall();

int readStatement();

int doWhile();

int writeStatement();

#endif
