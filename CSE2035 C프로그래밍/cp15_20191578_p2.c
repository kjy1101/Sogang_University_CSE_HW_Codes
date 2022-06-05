#include <stdio.h>
#include <stdlib.h>

typedef struct{
	float price; //가격
	float number; //개수
} Buying;

Buying getAverage(Buying *pBuying, int n);

int main(void){
	int N;
	Buying *pBuying;
	Buying result;
	pBuying=(Buying*)malloc(sizeof(Buying)*N);
	scanf("%d", &N);
	for(int i=0;i<N;i++)
		scanf("%f %f", &(pBuying[i].price), &(pBuying[i].number));
	result=getAverage(pBuying, N);
	printf("%.2f %.2f\n", result.price, result.number);

	return 0;}

Buying getAverage(Buying *pBuying, int n){
	Buying r;
	r.price=0;
	r.number=0;
	for(int i=0;i<n;i++){
		r.price+=pBuying[i].price;
		r.number+=pBuying[i].number;
	}
	r.price/=n;
	r.number/=n;
	return r;
}
