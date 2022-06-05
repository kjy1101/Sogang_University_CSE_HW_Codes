#include <stdio.h>

void snail(int n, int snail_array[20][20]);
void print_snail(int n, int snail_array[20][20]);

int main(void){
	int snail_array[20][20]={0};
	int n;

	printf("Input: ");
	scanf("%d", &n);
	
	int i;
	for(i=n;i>0;i--){
		snail(i, snail_array);
		print_snail(i, snail_array);
		printf("\n");}


	return 0;}



void snail(int n, int snail_array[20][20]){
	int value = 1; //시작하는 수
	int delta = 1; //열이랑 행 변화량(1이면 증가, -1이면 감소)
	int p; //?
	int col=0, row=-1; //col: 열, row: 행
	
	while(1){
		for(p=0;p<n;p++){
			row += delta;
			snail_array[col][row] = value;
			value++;}
		
		n--;
		if (n < 0) break;

		for(p=0;p<n;p++){
			col += delta;
			snail_array[col][row] = value;
			value++;}

		delta *= -1;}
	
}

void print_snail(int n, int snail_array[20][20]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%3d", snail_array[i][j]);}
		printf("\n");}}
