#ifndef PL0IMP_H
#define PL0IMP_H

#include "PL0.h"

//test
int isKeyWord(char *word){
	int i = 0, j = 12;

	while(i <= j){
		int k = (i + j) / 2;

		if(strcmp(word,KeyWord[k]) <= 0) j = k - 1;
		
		if(strcmp(word,KeyWord[k]) >= 0) i = k + 1;
	}

	return i - 1 > j ? 1 : 0;
}

int isDelimiter(char word){
	if(word == ',' || word == ';' || word == '.' || word == '(' || word == ')'){
		return 1;
	}

	return 0;	
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
	if((fin = fopen("Source.txt","r")) == NULL || (fout = fopen("Result.txt","w+")) == NULL)
	{
		printf("Open Error\n");
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
	return 0;
}

void printToScream(){
	FILE *fin;

	if((fin = fopen("Result.txt","r+")) == NULL){
		printf("OPEN ERROR\n");
		exit(0);
	}

	int id;
	char word[50];

	printf("0-Indentifier 1-Const 2-KeyWord 3-Operator 4-Delimiter\n");

	while(fscanf(fin,"%d %s",&id,word) != EOF){
		printf("%d\t%s\n",id,word);
	}

	fclose(fin);
}

#endif
