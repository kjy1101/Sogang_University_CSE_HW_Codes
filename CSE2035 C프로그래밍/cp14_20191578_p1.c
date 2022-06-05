#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	float comps;
	int vec_size;
}vector;

typedef float Distance;
typedef float Scalar;
typedef float Size;

Distance DistVector(vector *v1, vector *v2);
Scalar innerProduct(vector *v1, vector *v2);
Size vectorSize(vector *v);

int main(void){
	int n,m;
	vector *v1, *v2;

	scanf("%d", &n);
	v1=(vector*)malloc(sizeof(vector)*n);
	v1->vec_size=n;
	for(int i=0;i<n;i++)
		scanf("%f", &v1[i].comps);

	scanf("%d", &m);
	v2=(vector*)malloc(sizeof(vector)*m);
	v2->vec_size=m;
	for(int i=0;i<m;i++)
		scanf("%f", &v2[i].comps);

	printf("%.2f\n", vectorSize(v1));
	printf("%.2f\n", vectorSize(v2));
	if(n==m){
		printf("%.3f\n", DistVector(v1,v2));
		printf("%f\n", innerProduct(v1,v2));}

	return 0;}

Size vectorSize(vector *v){
	Size size=0;
	for(int i=0;i<v->vec_size;i++)
		size+=v[i].comps*v[i].comps;
	return sqrt(size);}

Distance DistVector(vector *v1, vector *v2){
	Distance d=0;
	for(int i=0;i<v1->vec_size;i++)
		d+=(v1[i].comps-v2[i].comps)*(v1[i].comps-v2[i].comps);
	return sqrt(d);}

Scalar innerProduct(vector *v1, vector *v2){
	Scalar inn=0;
	for(int i=0;i<v1->vec_size;i++)
		inn+=v1[i].comps*v2[i].comps;
	return inn;}
