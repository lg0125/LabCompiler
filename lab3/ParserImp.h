#ifndef PARSERIMP_H
#define PARSERIMP_H

#include "Parser.h"

int init(tNode **q,char *element){
	*q = (tNode *)malloc(sizeof(tNode));
	
	if((*q) == NULL){
		printf("init ERROR\n");
		exit(0);
	}
	
	strcpy((*q)->element, element);
	(*q)->num = 0;

	int i;
	for(i = 0;i < 20;i++) (*q)->child[i] = NULL;

	return 0;
}

int initNum(tNode **q,char *element,int childNum){
	*q = (tNode *)malloc(sizeof(tNode));
	
	if((*q) == NULL){
		printf("init ERROR\n");
		exit(0);
	}
	
	strcpy((*q)->element, element);
	(*q)->num = childNum;

	int i;
	for(i = 0;i < 20;i++) (*q)->child[i] = NULL;

	return 0;
}

int printNode(tNode *q){
	printf("%d %s\n",q->num,q->element);
	return 0;
}

void print(tNode *root,int num){
	tNode *p = root;
	
	if(p != NULL){
		
		for(int i = 0;i < num;i++){
			printf("|  ");
		}
		
		printf("|--%s\n",p->element);
		
		for(int i = 0;i < 20;i++){
			print(p->child[i],num + 1);
		}	
	}
}

int program(){
	p = scanner;
	
	char element[20] = "<SubProgram>";
	int childNum = 4;
	
	initNum(&tSubProgram,element,childNum);
	
	subProgram(&tSubProgram);
	
	if(strcmp(p->str, ".") == 0){
		char temp[] = ".";
		
		init(&tPoint,temp);
		
		tProgram->child[0] = tSubProgram;
		tProgram->child[1] = tPoint;
	}
	
	return 0;
}

int subProgram(tNode **tSubProgram){
	
	if(strcmp(p->str, "const") == 0){
		tNode *tConExplain;
		char temp[20] = "<ConstExplain>";
		
		init(&tConExplain,temp);
		
		(*tSubProgram) -> child[0] = tConExplain;
	}
	
	if(strcmp(p->str, "var") == 0){
		tNode *tVarExplain;
		char temp[20] = "<VarExplain>";
		
		init(&tVarExplain,temp);
		
		varExplain(&tVarExplain);
	
		(*tSubProgram) -> child[1] = tVarExplain;
	}
	
	if(strcmp(p->str, "procedure") == 0){
		tNode *tProcessExplain;
		char temp[20] = "<ProcessExplain>";
		init(&tProcessExplain,temp);
		
		processExplain(&tProcessExplain);
		
		(*tSubProgram) -> child[2] = tProcessExplain;
	}
	
	tNode *tStatement;
	char temp[20] = "<Statement>";
	int childNum = 1;
	
	initNum(&tStatement,temp,childNum);
	
	statement(&tStatement);
	
	(*tSubProgram) -> child[3] = tStatement;

	return 0;
}

//1
int conExplain(tNode **tConExplain){
	if(strcmp(p->str, "const") == 0){
		p = p->next;
		
		tNode *tConst, *tConstDef1;
		char str1[20] = "const";
		char str2[20] = "constDef";
		int childNum = 3;
		
		init(&tConst,str1);
		(*tConExplain) -> child[0] = tConst;

		initNum(&tConstDef1,str2,childNum);
		(*tConExplain) -> child[1] = tConstDef1;
		
		constDef(&tConstDef1);
	
		int count = 0;
		while(strcmp(p->str, ",")){
			count++; //child;
			
			tNode *temp;
			char str3[20] = ",";
			init(&temp,str3);
			(*tConExplain) -> child[2 * count] = temp;

			tNode *tConstDef2;
			initNum(&tConstDef2,str2,childNum);
			(*tConExplain) -> child[2 * count + 1] = tConstDef2;
			
			p = p->next;
		
			constDef(&tConstDef2);
		}

		if(strcmp(p->str, ";") == 0){
			p = p->next;
			
			tNode *temp;
			char str4[20] = ";";
			init(&temp,str4);
			
			(*tConExplain) -> child[2 * count + 2] = temp; 
		}else{
			printf("conExplain1 ERROR\n");
			exit(0);
		}
	}else{
		printf("conExplain2 ERROR\n");
		exit(0);
	}
	return 0;
}

int unsignedInt(tNode **tUnsignedInt){
	if(p->type == 1) {
		tNode *temp;
		init(&temp,p->str);
		(*tUnsignedInt) -> child[0] = temp;
		
		p = p->next;
	}
	else{
		printf("unsignedInt ERROR\n");
		exit(0);
	}
	
	return 0;
}

int id(tNode **tId){
	
	if(p->type == 0) {
		tNode *temp;
		init(&temp,p->str);
		(*tId) -> child[0] = temp;
		
		p = p->next;	
	}
	else{
		printf("id ERROR\n");
		exit(0);
	}
	
	return 0;
}

int constDef(tNode **tConstDef){
	tNode *tId;
	char str1[20] = "<Identifier>";
	init(&tId,str1);
	
	(*tConstDef) -> child[0] = tId;
	
	id(&tId);
	
	if(strcmp(p->str, "=") == 0){
		tNode *temp;
		char str2[20] = "=";
		init(&temp,str2);
		
		p = p->next;
		
		tNode *tUnsignedInt;
		char str3[20] = "<UnsignedInt>";
		init(&tUnsignedInt,str3);
		
		unsignedInt(&tUnsignedInt);
	}else{
		printf("constDef ERROR\n");
		exit(0);
	}
	
	return 0;
}

//2
int varExplain(tNode **tVarExplain){
	int childNum = 3;
	char str[20] = "<Identifier>";
	
	if(strcmp(p->str, "var") == 0){
		p = p->next;
		
		tNode *temp1;
		char str1[20] = "var";
		init(&temp1,str1);
		
		(*tVarExplain) -> child[0] = temp1;
		
		tNode *tId_1;
		initNum(&tId_1,str,childNum);
		
		(*tVarExplain) -> child[1] = tId_1;
		
		id(&tId_1);
		
		int count = 0;
		while(strcmp(p->str, ",") == 0){
			p = p->next;
			
			count++;
			
			tNode *temp2;
			char str2[20] = ",";
			init(&temp2,str2);
			
			(*tVarExplain) -> child[2 * count] = temp2;

			tNode *tId_2;
			initNum(&tId_2,str,childNum);
			
			(*tVarExplain) -> child[2 * count + 1] = tId_2;
			
			id(&tId_2);
		}
		
		if(strcmp(p->str, ";") == 0) {
			p = p->next;
			
			tNode *temp3;
			char str3[20] = ";";
			init(&temp3,str3);
			
			(*tVarExplain) -> child[count + 1] = temp3;
		}
		else{
			printf("varExplain1 ERROR\n");
			exit(0);
		}
	}else{
		printf("varExplain2 ERROR\n");
		exit(0);
	}
	
	return 0;
}

//3
int processHead(tNode **tProcessHead){
	
	if(strcmp(p->str, "procedure") == 0){
		p = p->next;
		
		tNode *temp;
		char str1[20] = "procedure";
		init(&temp,str1);
		
		(*tProcessHead) -> child[0] = temp;

		tNode *tId;
		char str2[20] = "<Identifier>";
		init(&tId,str2);
		
		(*tProcessHead) -> child[1] = tId;
		
		id(&tId);
		
		if(strcmp(p->str, ";") == 0) {
			p = p->next;
			
			tNode *temp1;
			char str3[20] = ";";
			init(&temp1,str3);
			
			(*tProcessHead) -> child[2] = temp1; //?
		}
		else{
			printf("processHead1 ERROR\n");
			exit(0);
		}
	}else{
		printf("processHead2 ERROR\n");
		exit(0);
	}
	
	return 0;
}

int processExplain(tNode **tProcessExplain){
	
	int childNum = 3;
	tNode *tProcessHead;
	char str1[20] = "<ProcessHead>";
	initNum(&tProcessHead,str1,childNum);
	
	(*tProcessExplain) -> child[0] = tProcessHead;
	
	tNode *_tSubProgram;
	char str2[20] = "<SubProgram>";
	init(&_tSubProgram,str2);
	
	(*tProcessExplain) -> child[1] = _tSubProgram;
	
	processHead(&tProcessHead);
	subProgram(&_tSubProgram);
	
	if(strcmp(p->str, ";") == 0){
		tNode *temp;
		char str3[20] = ";";
		init(&temp,str3);
		
		(*tProcessExplain) -> child[2] = temp;
		
		p = p->next;
		
		int count = 0;
		while(strcmp(p->str, "procedure") == 0){
			count++;
			
			tNode *_tProcessExplain;
			char str4[20] = "<ProcessExplain>";
			init(&_tProcessExplain,str4);
			
			(*tProcessExplain) -> child[count + 2] = _tProcessExplain;
			
			processExplain(&_tProcessExplain);
		}
	}else{
		printf("processExplain ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4
int statement(tNode **tStatement){
	int childNum1 = 3;
	int childNum2 = 2;
	
	if(p->type == 0){
		tNode *tAssignmentStatement;
		char str[20] = "<AssignStatement>";
		initNum(&tAssignmentStatement,str,childNum1);
		
		(*tStatement) -> child[0] = tAssignmentStatement;
		
		assignmentStatement(&tAssignmentStatement);
		
	}
	else if(strcmp(p->str, "if") == 0){
		tNode *tConditionStatement;
		char str[20] = "<CondiStatement>";
		initNum(&tConditionStatement,str,childNum1);
		
		(*tStatement) -> child[0] = tConditionStatement;
		
		conditionStatement(&tConditionStatement);
	}
	else if(strcmp(p->str, "while") == 0) {
		tNode *tDoWhile;
		char str[20] = "<DWStatement>";
		initNum(&tDoWhile,str,childNum1);
		
		(*tStatement) -> child[0] = tDoWhile;
		
		doWhile(&tDoWhile);
	}
	else if(strcmp(p->str, "call") == 0) {
		tNode *tProcessCall;
		char str[20] = "<PCStatement>";
		initNum(&tProcessCall,str,childNum2);
		
		(*tStatement) -> child[0] = tProcessCall;
		
		processCall(&tProcessCall);
	}
	else if(strcmp(p->str, "read") == 0) {
		tNode *tReadStatement;
		char str[20] = "<ReadStament>";
		initNum(&tReadStatement,str,childNum2);
		
		(*tStatement) -> child[0] = tReadStatement;
		
		readStatement(&tReadStatement);
	}
	else if(strcmp(p->str, "write") == 0){
		tNode *tWriteStatement;
		char str[20] = "<WriteStatement>";
		initNum(&tWriteStatement,str,childNum2);
		
		(*tStatement) -> child[0] = tWriteStatement;
		
		writeStatement(&tWriteStatement);
	}
	else if(strcmp(p->str, "begin") == 0){
		tNode *tCompoundStatement;
		char str[20] = "<CompoundState>";
		initNum(&tCompoundStatement,str,childNum2);

		(*tStatement) -> child[0] = tCompoundStatement;
		
		compoundStatement(&tCompoundStatement);
	}
	return 0;
}

//4.1
int mulDivide(tNode **tMulDivide){
	if(strcmp(p->str, "*") == 0 || strcmp(p->str, "/") == 0){
		tNode *temp;
		init(&temp,p->str);
		
		(*tMulDivide) -> child[0] = temp;
		
		p = p->next;
	}
	else{
		printf("mulDivide ERROR\n");
		exit(0);
	}

	return 0;
}

int factor(tNode **tFactor){
	if(p->str[0] >= 'a' && p->str[0] <= 'z'){
		tNode *tId;
		char str[20] = "<Identifier>";
		init(&tId,str);
		
		(*tFactor) -> child[0] = tId;
		
		id(&tId);
	}
	else if(p->str[0] >= '0' && p->str[0] <= '9'){
		tNode *tUnsignedInt;
		char str[20] = "<UnsignedInt>";
		init(&tUnsignedInt,str);
		
		(*tFactor) -> child[0] = tUnsignedInt;
		
		unsignedInt(&tUnsignedInt);
	}
	else if(strcmp(p->str, "(") == 0){
		tNode *temp;
		char str1[20] = "(";
		init(&temp,str1);
		
		(*tFactor) -> child[0] = temp;
		
		tNode *tExpression;
		char str2[20] = "<Expression>";
		init(&tExpression,str2);
		
		(*tFactor) -> child[1] = tExpression;
		
		expression(&tExpression);
	
		if(strcmp(p->str, ")") == 0){
			tNode *temp1;
			char str3[20] = ")";
			init(&temp1,str3);
			
			(*tFactor) -> child[2] = temp1;
			
			p = p->next;
		}else{
			printf("factor1 ERROR\n");
			exit(0);
		}
	}else{
		printf("factor2 ERROR\n");
		exit(0);
	}

	return 0;
}

int addSubtract(tNode **tAddSubtract){
	if(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0){
		tNode *temp;
		init(&temp,p->str);
		
		(*tAddSubtract) -> child[0] = temp;
		
		p = p->next;
	}
	else{
		printf("addSubstract ERROR\n");
		exit(0);
	}
	
	return 0;
}

int item(tNode **tItem){
	tNode *tFactor1;
	char str1[20] = "<Factor>";
	init(&tFactor1,str1);
	
	(*tItem) -> child[0] = tFactor1;
	
	factor(&tFactor1);
	
	int count = 0;
	while(strcmp(p->str, "*") == 0 || strcmp(p->str, "/") == 0){
		count++;
		
		tNode *tMulDivide;
		char str2[20] = "<MulDivide>";
		init(&tMulDivide,str2);
		
		(*tItem) -> child[2 * count - 1] = tMulDivide;
		
		mulDivide(&tMulDivide);
		
		tNode *tFactor2;
		init(&tFactor2,str1);
		
		(*tItem) -> child[2 * count] = tFactor2;
		
		factor(&tFactor2);
	}	
	
	return 0;
}

int expression(tNode **tExpression){
	
	if(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0){ 
		p = p->next;
		
		tNode *temp;
		init(&temp,p->str);
		
		(*tExpression) -> child[0] = temp;
	}
	
	tNode *tItem;
	char str1[20] = "<Item>";
	init(&tItem,str1);
	
	(*tExpression) -> child[1] = tItem;
	
	item(&tItem);
	
	int count = 0;
	while(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0){
		count++;
		
		tNode *tAddSubtract;
		char str2[20] = "<AddSubtract>";
		init(&tAddSubtract,str2);
		
		(*tExpression) -> child[2 * count] = tAddSubtract;
		
		tNode *_tItem;
		init(&_tItem,str1);
		
		(*tExpression) -> child[2 * count + 1] = _tItem;
			
		addSubtract(&tAddSubtract);
		
		item(&_tItem);
	}
	
	
	return 0;
}


int assignmentStatement(tNode **tAssignmentStatement){
	tNode *tId;
	char str1[20] = "<Identifier>";
	init(&tId,str1);
	
	(*tAssignmentStatement) -> child[0] = tId;
	
	id(&tId);
	
	if(strcmp(p->str, ":=") == 0){
		p = p->next;
		
		tNode *temp;
		char str2[20] = ":=";
		init(&temp,str2);
		
		(*tAssignmentStatement) -> child[0] = temp;
		
		tNode *tExpression;
		char str3[20] = "<Expression>";
		init(&tExpression,str3);
		
		(*tAssignmentStatement) -> child[3] = tExpression; //?
		
		expression(&tExpression);
	}else{
		printf("assignmentStatement ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4.2
int relationship(tNode **tRelationship){
	if(strcmp(p->str, "=") == 0  ||
	   strcmp(p->str, "#") == 0  ||
	   strcmp(p->str, "<") == 0  ||
	   strcmp(p->str, "<=") == 0 ||
	   strcmp(p->str, ">") == 0  ||
	   strcmp(p->str, ">=") == 0){
			tNode *temp;
			init(&temp,p->str);
		
			(*tRelationship) -> child[0] = temp;
		   
			p = p->next;
	}else{
		printf("relationship ERROR\n");
		exit(0);
	}
	
	return 0;
}

int conditions(tNode **tConditions){
	if(strcmp(p->str, "odd") == 0){
		p = p->next;
		
		tNode *temp1;
		char str1[20] = "odd";
		init(&temp1,str1);
		
		(*tConditions) -> child[0] = temp1;
		
		tNode *tExpression;
		char str2[20] = "<Expression>";
		init(&tExpression,str2);
		
		(*tConditions) -> child[1] = tExpression;
		
		expression(&tExpression);
	}
	else{
		//1
		tNode *tExpression1;
		char str3[20] = "<Expression>";
		init(&tExpression1,str3);
		
		(*tConditions) -> child[0] = tExpression1;
		
		expression(&tExpression1);
		//2
		tNode *tRelationship;
		char str4[20] = "<Relationship>";
		init(&tRelationship,str4);
		
		(*tConditions) -> child[1] = tRelationship;
		
		relationship(&tRelationship);
		
		//3
		tNode *tExpression2;
		
		init(&tExpression2,str3);
		
		(*tConditions) -> child[2] = tExpression2;
		
		expression(&tExpression2);
	}
	return 0;
}

int conditionStatement(tNode **tConditionStatement){
	if(strcmp(p->str, "if") == 0){
		tNode *temp1;
		char str1[20] = "if";
		init(&temp1,str1);
		
		(*tConditionStatement) -> child[0] = temp1;
		
		p = p->next;
		
		tNode *tConditions;
		char str2[20] = "<Condition>";
		init(&tConditions,str2);
		
		(*tConditionStatement) -> child[1] = tConditions;
		
		conditions(&tConditions);
	
		if(strcmp(p->str, "then") == 0){
			p = p->next;
			
			tNode *temp2;
			char str3[20] = "then";
			init(&temp2,str3);
			
			(*tConditionStatement) -> child[0] = temp2; //?
			
			
			tNode *tStatement;
			char str4[20] = "<Statement>";
			init(&tStatement,str4);
			
			(*tConditionStatement) -> child[1] = tStatement;//?
			
			statement(&tStatement);
		}else{
			printf("conditionStatement1 ERROR\n");
			exit(0);
		}
	}else{
		printf("conditionStatement2 ERROR\n");
		exit(0);
	}
	return 0;
}

//4.3
int doWhile(tNode **tDoWhile){
	if(strcmp(p->str, "while") == 0){
		tNode *temp1;
		char str1[20] = "while";
		init(&temp1,str1);
		
		(*tDoWhile) -> child[0] = temp1;
		
		p = p->next;
		
		tNode *tConditions;
		char str2[20] = "<Condition>";
		init(&tConditions,str2);
		
		(*tDoWhile) -> child[1] = tConditions;
		
		conditions(&tConditions);
		
		if(strcmp(p->str, "do") == 0){
			tNode *temp2;
			char str3[20] = "do";
			init(&temp2,str3);
			
			(*tDoWhile) -> child[2] = temp2;
				
			p = p->next;
			
			tNode *tStatement;
			char str4[20] = "<Statement>";
			init(&tStatement,str4);
			
			(*tDoWhile) -> child[3] = tStatement;
				
			statement(&tStatement);
		}
		
	}else{
		printf("doWhile2 ERROR\n");
		exit(0);
	}
	return 0;
}

//4.4
int processCall(tNode **tProcessCall){
	if(strcmp(p->str, "call") == 0){
		p = p->next;
		
		tNode *tId;
		char str[20] = "<Identifier>";
		init(&tId,str);
		
		(*tProcessCall) -> child[0] = tId;
		
		id(&tId);
	}else{
		printf("processCall ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4.5
int readStatement(tNode **tReadStatement){
	
	if(strcmp(p->str, "read") == 0){
		tNode *temp1;
		char str1[20] = "read";
		init(&temp1,str1);
		
		(*tReadStatement) -> child[0] = temp1;
		
		p = p->next;
		
		if(strcmp(p->str, "(") == 0){
			tNode *temp2;
			char str2[20] = "(";
			init(&temp2,str2);
			
			(*tReadStatement) -> child[1] = temp2;
			
			p = p->next;
			
			tNode *tId1;
			char str[20] = "<Identifier>";
			init(&tId1,str);
			
			id(&tId1);
			
			int count = 0;
			while(strcmp(p->str, ",") == 0){
				tNode *temp3;
				char str3[20] = ",";
				init(&temp3,str3);
				
				(*tReadStatement) -> child[2 * count + 1] = temp3;
				
				p = p->next;
				
				tNode *tId2;
				init(&tId2,str);
				
				(*tReadStatement) -> child[2 * count + 2] = tId2;
				
				id(&tId2);
			}
			
			if(strcmp(p->str, ")") == 0){
				tNode *temp4;
				char str4[20] = ")";
				init(&temp4,str4);
				
				(*tReadStatement) -> child[2 * count + 3] = temp4;
				
				p = p->next;
			}
			else{
				printf("readStatement1 ERROR\n");
				exit(0);
			}
		}else{
			printf("readStatement2 ERROR\n");
			exit(0);
		}
	}else{
		printf("readStatement3 ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4.6
int writeStatement(tNode **tWriteStatement){
	if(strcmp(p->str, "write") == 0){
		tNode *temp1;
		char str1[20] = "write";
		init(&temp1,str1);
		
		(*tWriteStatement) -> child[0] = temp1;
		
		p = p->next;
		
		if(strcmp(p->str, "(") == 0){
			tNode *temp2;
			char str2[20] = "(";
			init(&temp2,str2);
			
			(*tWriteStatement) -> child[1] = temp2;
			
			p = p->next;
			
			tNode *tExpression1;
			char str[20] = "<Expression>";
			init(&tExpression1,str);
			
			(*tWriteStatement) -> child[2] = tExpression1;
			
			expression(&tExpression1);
			
			int count = 0;
			while(strcmp(p->str, ",") == 0){
				count++;
				
				p = p->next;
				
				tNode *temp3;
				char str3[20] = "(";
				init(&temp3,str3);
				
				(*tWriteStatement) -> child[2 * count + 1] = temp3;
				
				tNode *tExpression2;
				init(&tExpression2,str);
			
				(*tWriteStatement) -> child[2 * count + 2] = tExpression2;
			
				expression(&tExpression2);	
			}
			
			if(strcmp(p->str, ")") == 0){
				tNode *temp4;
				char str4[20] = ")";
				init(&temp4,str4);
				
				(*tWriteStatement) -> child[2 * count + 3] = temp4;
					
				p = p->next;
			}
			else{
				printf("writeStatement1 ERROR\n");
				exit(0);
			}
		}else{
			printf("writeStatement2 ERROR\n");
			exit(0);
		}
	}else{
		printf("writeStatement3 ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4.7
int compoundStatement(tNode **tCompoundStatement){
	if(strcmp(p->str, "begin") == 0){
		tNode *temp1;
		char str1[20] = "begin";
		init(&temp1,str1);
		
		(*tCompoundStatement) -> child[0] = temp1;

		p = p->next;
		
		tNode *tStatement1;
		char str[20] = "<Statement>";
		init(&tStatement1,str);
		
		(*tCompoundStatement) -> child[1] = tStatement1;
		
		statement(&tStatement1);
		
		int count = 0;
		while(strcmp(p->str, ";") == 0){
			p = p->next;
			
			count++;
			
			tNode *temp2;
			char str2[20] = "begin";
			init(&temp2,str2);
			
			(*tCompoundStatement) -> child[2 * count] = temp2;
			
			tNode *tStatement2;
			init(&tStatement1,str);
		
			(*tCompoundStatement) -> child[2 * count + 1] = tStatement2;
		
			statement(&tStatement2);
		}
		
		if(strcmp(p->str, "end") == 0){
			tNode *temp3;
			char str3[20] = "end";
			init(&temp3,str3);
			
			(*tCompoundStatement) -> child[2 * count + 2] = temp3;
		
			p = p->next;
		}
		else{
			printf("compoundStatement1 ERROR\n");
			exit(0);
		}
	}else{
		printf("compoundStatement2 ERROR\n");
		exit(0);
	}
	
	return 0;
}


#endif