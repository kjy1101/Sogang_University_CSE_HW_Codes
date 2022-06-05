#include <stdio.h>
#include <stdlib.h>

int main(void){
	int N;
	int *pibo;
	scanf("%d", &N);
	pibo=malloc(N*sizeof(int));
	pibo[0]=1;
	pibo[1]=1;
	for(int i=2;i<N;i++){
		pibo[i]=pibo[i-2]+pibo[i-1];
	}
	for(int i=0;i<N;i++)
		printf("%d ", pibo[i]);
	printf("\n");
	free(pibo);
	return 0;}
