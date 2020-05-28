#ifndef SCANNER_H
#define SCANNER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef enum SymEnum{
	Identifier = 0,
	Const = 1,
	Key = 2,
	Operator = 3,
	Delimiter = 4
}SymEnum;

typedef struct node{
	SymEnum type;
	char str[20];
	struct node *next;
}node; 

node *scanner;

char KeyWord[13][15] = {
	"begin","call","const","do","end",
	"if","odd","procedure","read","then",
	"var","while","write"
};

int isKeyWord(char *word);

int isDelimiter(char word);

int isOperator(char *word);

int isOperator(char *word);

int isConst(char *word);

int isSame(char f,char s);

SymEnum typeOfWord(char *word);

int getSym();

int getScanner();

int printScanner();
#endif