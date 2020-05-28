#ifndef SCANNERIMP_H
#define SCANNERIMP_H

#include "Scanner.h"

int isKeyWord(char *word){
	int i = 0, j = 12;

	while(i <= j){
		int k = (i + j) / 2;

		if(strcmp(word,KeyWord[k]) <= 0) j = k - 1;

		if(strcmp(word,KeyWord[k]) >= 0) i = k + 1;
	}
	
	return i - 1 > j ? 1 : 0;
}

int isOperator(char *word){
	if(word[0] == '+' || word[0] == '-' || word[0] == '*' || word[0] == '/' || 
	   word[0] == '<' || word[0] == '>' || word[0] == '#' || word[0] == '=' ||
	   strcmp(word,":=") == 0 || strcmp(word,">=") == 0 ||
	   strcmp(word,"<=") == 0){
		return 1;
	}

	return 0;
}

int isDelimiter(char word){
	if(word == ',' || word == ';' || word == '.' || word == '(' || word == ')'){
		return 1;
	}
	return 0;
}

int isConst(char *word){
	if(word[0] >= '0' && word[0] <= '9') return 1;
	return 0;
}

int isSame(char f,char s){
	int bf = (f >= '0' && f <= '9' || f >= 'a' && f <= 'z' || f >= 'A' && f <= 'Z') ? 1 : 0;
	int bs = (s >= '0' && s <= '9' || s >= 'a' && s <= 'z' || s >= 'A' && s <= 'Z') ? 1 : 0;
	return bf == bs;
}

SymEnum typeOfWord(char *word){
	if(isKeyWord(word)) return Key;
	else if(isConst(word)) return Const;
	else if(isOperator(word)) return Operator;
	else return Identifier;
}

int getSym(){
	FILE *fin,*fout;

	if((fin = fopen("Source.txt","r")) == NULL || (fout = fopen("Result.txt","w+")) == NULL){
		printf("OPEN ERROR\n");
		exit(0);
	}

	SymEnum SYM;

	char word[50];
	word[0] = '\0';

	int len = 0;
	char ch;

	while(fscanf(fin,"%c",&ch) != EOF){
		if(ch == ' ' || ch == '\n' || ch == '\t'){
			if(len){
				SYM = typeOfWord(word);

				fprintf(fout,"%d %s\n",SYM,word);

				len = 0;
				word[len] = '\0';
			}
		}else if(isDelimiter(ch)){
			if(len){
				SYM = typeOfWord(word);

				fprintf(fout,"%d %s\n",SYM,word);

				SYM = Delimiter;

				fprintf(fout,"%d %c\n",SYM,ch);

				len = 0;
				word[len] = '\0';
			}else{
				SYM = Delimiter;

				fprintf(fout,"%d %c\n",SYM,ch);

				len = 0;
				word[len] = '\0';
			}
		}else{
			if(len > 0){
				if(isSame(word[len - 1],ch)){
					word[len++] = ch;
					word[len] = '\0';
				}else{
					SYM = typeOfWord(word);

					fprintf(fout,"%d %s\n",SYM,word);

					len = 0;
					word[len++] = ch;
					word[len] = '\0';
				}
			}else{
				word[len++] = ch;
				word[len] = '\0';
			}
		}
	}
	fclose(fin);
	fclose(fout);
}

int getScanner(){
	FILE * fin;

	if((fin = fopen("Result.txt","r+")) == NULL){
		printf("OPEN ERROR\n");
		exit(0);
	}

	int id;
	char word[20];

	scanner = (node *)malloc(sizeof(node));

	if(fscanf(fin,"%d %s",&id,word) != EOF){
		scanner->type = id;
		strcpy(scanner->str, word);
		scanner->next = NULL;
	}

	node *q = scanner;
	while(fscanf(fin,"%d %s",&id,word) != EOF){
		node *p = (node *)malloc(sizeof(node));
		
		p->type = id;
		strcpy(p->str, word);
		p->next = NULL;

		q->next = p;
		q = p;
	}
	q->next = NULL;

	fclose(fin);
	return 0;
}



int printScanner(){
	node *p = scanner;

	while(p != NULL){
		printf("[%d %s]\n",p->type,p->str);
		p = p->next;
	}

	return 0;
}				


#endif
