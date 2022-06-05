#include <stdio.h>

void dec2oct(int *a1, int *a2, int *a3, int *a4, int num);
void dec2hex(char *b1, char *b2, char *b3, int num);
char digit2hex(int b);

int main(void){
	int num;
	scanf("%d", &num);
	int a1=0, a2=0, a3=0, a4=0;
	char b1=0, b2=0, b3=0;
	dec2oct(&a1, &a2, &a3, &a4, num);
	dec2hex(&b1, &b2, &b3, num);
	return 0;
}

void dec2oct(int *a1, int *a2, int *a3, int *a4, int num){
	*a1 = ((num / 8) / 8) / 8;
	*a2 = ((num / 8) / 8) % 8;
	*a3 = (num / 8) % 8;
	*a4 = num % 8;
	printf("%04o\n", num);
	printf("%d%d%d%d\n", *a1, *a2, *a3, *a4);
	return;
}

void dec2hex(char *b1, char *b2, char *b3, int num){
	*b1 = (num / 16) / 16 + 48;
	*b2 = (num / 16) % 16 + 48;
	*b3 = num % 16 + 48;
	printf("%03X\n", num);
	printf("%c%c%c\n", digit2hex(*b1), digit2hex(*b2), digit2hex(*b3));
	return;
}

char digit2hex(int b){
	if (b >= 58)
		b += 7;
	return b;
}
