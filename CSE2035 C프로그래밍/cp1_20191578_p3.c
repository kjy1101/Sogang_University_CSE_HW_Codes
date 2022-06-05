#include <stdio.h>
void *function(void *pa, void *pb, int option);

int main(void){
	int option;
	int a,b;
	float fa,fb;
	double da,db;
	void *pa, *pb, *ans;

	scanf("%d", &option);
	switch(option){
		case 0: scanf("%d %d", &a, &b);
				pa=&a;
				pb=&b;
				ans=function(pa,pb,option);
				printf("%d\n", *(int*)ans);
				break;
		case 1: scanf("%f %f", &fa, &fb);
				pa=&fa;
				pb=&fb;
				ans=function(pa,pb,option);
				printf("%f\n", *(float*)ans);
				break;
		case 2: scanf("%lf %lf", &da, &db);
				pa=&da;
				pb=&db;
				ans=function(pa,pb,option);
				printf("%lf\n", *(double*)ans);
				break;
	}
	return 0;}

void *function(void *pa, void *pb, int option){
	switch(option){
		case 0: if(*(int*)pa<=*(int*)pb)
					return pa;
				else
					return pb;
		case 1: if(*(float*)pa<=*(float*)pb)
					return pa;
				else
					return pb;
		case 2: if(*(double*)pa<=*(double*)pb)
					return pa;
				else
					return pb;
	}

}
