#include <stdio.h>
#include <stdlib.h>

typedef struct{
	float coef;
	int expon;
}poly;

poly *poly_sum(int n, int m, poly *a, poly *b);

int main(void){
	int n,m;
	poly *a, *b;
	scanf("%d %d", &n, &m);
	a=(poly*)malloc(sizeof(poly)*n);
	b=(poly*)malloc(sizeof(poly)*m);
	for(int i=0;i<n;i++)
		scanf("%f %d", &a[i].coef, &a[i].expon);
	for(int j=0;j<m;j++)
		scanf("%f %d", &b[j].coef, &b[j].expon);

	poly *result;
	result=poly_sum(n,m,a,b);
	
	printf("%.2fx^%d", result[0].coef, result[0].expon);
	int i=1;
	while(result[i].expon!=0){
		printf("+%.2fx^%d", result[i].coef, result[i].expon);
		i++;}
	printf("\n");
	return 0;}

poly *poly_sum(int n, int m, poly *a, poly *b){
	int i=0,j=0,k=0;
	poly *result;
	result=(poly*)malloc(sizeof(poly)*(n+m));
	while(i<n&&j<m){
		if(a[i].expon<b[j].expon)
			result[k++]=a[i++];
		else if(a[i].expon==b[j].expon){
			if(a[i].coef+b[j].coef!=0){
				result[k].coef=a[i].coef+b[j].coef;
				result[k].expon=a[i].expon;
				k++;}
			i++;j++;}
		else
			result[k++]=b[j++];}
	while(i<n) result[k++]=a[i++];
	while(j<m) result[k++]=b[j++];
	return result;
}
