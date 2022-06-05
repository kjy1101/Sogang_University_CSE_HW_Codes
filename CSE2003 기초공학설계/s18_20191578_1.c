#include <stdio.h>
char toUppercase(char a);

int main(void){
	char sent[50];
	int i;
	char big;
	for (i=0;i<50;i++){
		scanf("%c", &sent[i]);}

	for (i=0;i<50;i++){
		big = toUppercase(sent[i]);
		printf("%c", big);}

//	for (i=0;i<50;i++){
//		printf("%c", sent[i]);}

	printf("\n");
	return 0;}


char toUppercase(char a){
	if (a < 97)
//		printf("%c", a);
		return a;
	else
//		printf("%c", a-32);}
		return a-32;}
