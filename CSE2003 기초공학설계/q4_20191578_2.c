#include <stdio.h>

int main(void){
	char a=0, b=0;
	scanf("%c %c", &a, &b);
	a = a-48;
	b = b-48;
//	printf("%d %d\n", a, b);
	char result=0;

	result = (a * b)%26;

//	printf("%c %c\n", a+17, b+17);
	printf("%c\n", result+65);

	return 0;}
