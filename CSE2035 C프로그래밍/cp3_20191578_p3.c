#include <stdio.h>
void mat_mul(int a[100][100],int b[100][100],int c[100][100],int N);

int main(void){
	int N;
	int a[100][100], b[100][100], c[100][100];
	scanf("%d", &N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d", &a[i][j]);}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d", &b[i][j]);}
	mat_mul(a,b,c,N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			printf("%d ", c[i][j]);
		printf("\n");}
}

void mat_mul(int a[100][100], int b[100][100], int c[100][100], int N){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<N;k++){
				c[i][j]+=a[i][k]*b[k][j];}}}

}
