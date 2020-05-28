#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct tNode{
	int num;
	char element[20];
	struct tNode *child[20];
}tNode;

int init(tNode *q,char *element){
	q = (tNode *)malloc(sizeof(tNode));
	
	if((q) == NULL){
		printf("init ERROR\n");
		exit(0);
	}
	
	strcpy((q)->element, element);
	(q)->num = 0;

	int i;
	for(i = 0;i < 20;i++) (q)->child[i] = NULL;

	return 0;
}

int main(){
	tNode *q;
	char str[20] = "helloword";
	init(q,str);
	printf("%d %s",q->num,q->element);
	

	return 0;
}
