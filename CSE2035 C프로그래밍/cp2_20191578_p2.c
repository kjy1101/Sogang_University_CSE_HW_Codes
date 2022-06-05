#include <stdio.h>
void f(int *H, int *M, int *S, int T);

int main(void){
	int H,M,S,T;
	scanf("%d %d %d %d", &H, &M, &S, &T);
	f(&H, &M, &S, T);
	printf("%02d:%02d:%02d\n",H,M,S);

	return 0;}

void f(int *H, int *M, int *S, int T){
	*S+=T;
	int temp=0;
	int hour=0;
	while(*S>=60){
		*S-=60;
		temp++;
	}
	*M+=temp;
	while(*M>=60){
		*M-=60;
		hour++;}
	*H+=hour;
}
