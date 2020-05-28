#ifndef PARSERIMP_H
#define PARSERIMP_H

#include "Parser.h"

int program(){
	
	p = scanner;

	subProgram();

	if(strcmp(p->str, ".") == 0){
		p = p->next;
		
		printf("SUCCESS!\n");
	}else{
		printf(". ERROR\n");
		
		exit(0);
	}
	
	return 0;
}


int unsignedInt(){
	
	if(p->type == 1) p = p->next;
	
	else{
		printf("unsignedInt ERROR\n");
		exit(0);
	}
	
	return 0; 
}

int id(){
	
	if(p->type == 0) p = p->next;
	
	else{
		printf("id ERROR\n");
		exit(0);
	}

	return 0;
}

int constDef(){
	id();
	
	if(strcmp(p->str, "=") == 0){
		p = p->next;
		
		unsignedInt();
	}else{
		printf("constDef ERROR\n");
		exit(0);
	}

	return 0;
}

//1
int conExplain(){
	if(strcmp(p->str, "const") == 0){
		p = p->next;

		constDef();//not
	
		while(strcmp(p->str, ",")){
			p = p->next;
		
			constDef();
		}

		if(strcmp(p->str, ";") == 0){
			p = p->next;
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

//2
int varExplain(){
	
	if(strcmp(p->str, "var") == 0){
		p = p->next;
		
		id();
		
		while(strcmp(p->str, ",") == 0){
			p = p->next;
			
			id();
		}
		
		if(strcmp(p->str, ";") == 0) p = p->next;
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


int processHead(){
	if(strcmp(p->str, "procedure") == 0){
		p = p->next;
		
		id();
		
		if(strcmp(p->str, ";") == 0) p = p->next;
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

//3
int processExplain(){
	
	processHead();
	
	subProgram();
	
	if(strcmp(p->str, ";") == 0){
		p = p->next;
		
		while(strcmp(p->str, "procedure") == 0) processExplain();
	}else{
		printf("processExplain ERROR\n");
		exit(0);
	}
	
	return 0;
}

int subProgram(){
	
	if(strcmp(p->str, "const") == 0) conExplain();

	if(strcmp(p->str, "var") == 0) varExplain();

	if(strcmp(p->str, "procedure") == 0) processExplain();

	statement();

	return 0;
}

//4
int statement(){
	if(p->type == 0) assignmentStatement();
	else if(strcmp(p->str, "if") == 0) conditionStatement();
	else if(strcmp(p->str, "while") == 0) doWhile();
	else if(strcmp(p->str, "call") == 0) processCall();
	else if(strcmp(p->str, "read") == 0) readStatement();
	else if(strcmp(p->str, "write") == 0) writeStatement();
	else if(strcmp(p->str, "begin") == 0) compoundStatement();
	
	return 0;
}

int addSubstract(){

	if(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0) p = p->next;
	else{
		printf("addSubstract ERROR\n");
		exit(0);
	}

	return 0;
}

int mulDivide(){

	if(strcmp(p->str, "*") == 0 || strcmp(p->str, "/") == 0) p = p->next;
	else{
		printf("mulDivide ERROR\n");
		exit(0);
	}

	return 0;
}

int factor(){
	if(p->str[0] >= 'a' && p->str[0] <= 'z') id();
	else if(p->str[0] >= '0' && p->str[0] <= '9') unsignedInt();
	else if(strcmp(p->str, "(") == 0){
		expression();
	
		if(strcmp(p->str, ")") == 0){
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

int item(){
	factor();

	while(strcmp(p->str, "*") == 0 || strcmp(p->str, "/") == 0){
		mulDivide();
		
		factor();
	}	


	return 0;
}

int expression(){
	
	if(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0) p = p->next;

	item();

	while(strcmp(p->str, "+") == 0 || strcmp(p->str, "-") == 0){
		
		addSubstract();
		
		item();
	}


	return 0;
}

//4.1
int assignmentStatement(){
	id();

	if(strcmp(p->str, ":=") == 0){
		p = p->next;
		expression();
	}else{
		printf("assignmentStatement ERROR\n");
		exit(0);
	}
	return 0;
}

int relationship(){
	if(strcmp(p->str, "=") == 0  ||
	   strcmp(p->str, "#") == 0  ||
	   strcmp(p->str, "<") == 0  ||
	   strcmp(p->str, "<=") == 0 ||
	   strcmp(p->str, ">") == 0  ||
	   strcmp(p->str, ">=") == 0){
		   p = p->next;
	}else{
		printf("relationship ERROR\n");
		exit(0);
	}
	return 0;
}

int conditions(){
	if(strcmp(p->str, "odd") == 0) {
		p = p->next;
		expression();
	}
	else{
		expression();
		
		relationship();
		
		expression();
	}
	return 0;
}

//4.2
int conditionStatement(){
	if(strcmp(p->str, "if") == 0){
		p = p->next;
		
		conditions();
		
		if(strcmp(p->str, "then") == 0){
			p = p->next;
			
			statement();
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
int doWhile(){
	if(strcmp(p->str, "while") == 0){
		p = p->next;
		
		conditions();
		
		if(strcmp(p->str, "do") == 0){
			p = p->next;
			
			statement();
		}
		
	}else{
		printf("doWhile2 ERROR\n");
		exit(0);
	}

	return 0;
}

//4.4
int processCall(){
	if(strcmp(p->str, "call") == 0){
		p = p->next;
		
		id();
	}else{
		printf("processCall ERROR\n");
		exit(0);
	}
	
	return 0;
}

//4.5
int readStatement(){
	if(strcmp(p->str, "read") == 0){
		p = p->next;
		
		if(strcmp(p->str, "(") == 0){
			p = p->next;
			
			id();
			
			while(strcmp(p->str, ",") == 0){
				p = p->next;
				
				id();
			}
			
			if(strcmp(p->str, ")") == 0) p = p->next;
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
int writeStatement(){
	if(strcmp(p->str, "write") == 0){
		p = p->next;
		
		if(strcmp(p->str, "(") == 0){
			p = p->next;
			
			expression();
			
			while(strcmp(p->str, ",") == 0){
				p = p->next;
				
				expression();
			}
			
			if(strcmp(p->str, ")") == 0) p = p->next;
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
int compoundStatement(){
	if(strcmp(p->str, "begin") == 0){
		p = p->next;
		
		statement();
		
		while(strcmp(p->str, ";") == 0){
			p = p->next;
			
			statement();
		}
		
		if(strcmp(p->str, "end") == 0) p = p->next;
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
