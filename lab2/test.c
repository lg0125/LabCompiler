#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct tp{
	char str[10];
}tp;

int main(){
	tp *t = (tp *)malloc(sizeof(tp));

	char tr[10] = "ip";
		
	strcpy(t->str,tr);

	printf("%c\n",t->str[0]);

	//int ans = strcmp(str,"ip"); 

	//printf("%d\n",ans);

	return 0;
}
