#include <stdio.h>

int main(void){
	int a,b,c;
	int *pa, *pb, *pc;
	scanf("%d %d %d", &a, &b, &c);
	pa=&a;
	pb=&b;
	pc=&c;

	int *min, *max;
	if(*pa>*pb){
		if(*pc>*pa){
			max=pc;}
		else{
			max=pa;}}
	else{
		if(*pc>*pb){
			max=pc;}
		else{
			max=pb;}
	}

	if(*pa<*pb){
		if(*pc<*pa)
			min=pc;
		else
			min=pa;}
	else{
		if(*pc<*pb)
			min=pc;
		else
			min=pb;}

	/*printf("a: %d address: %p\n",*pa,pa);
	printf("b: %d address: %p\n",*pb,pb);
	printf("c: %d address: %p\n",*pc,pc);
	printf("max: %d address: %p\n", *max, max);
	printf("min: %d address: %p\n", *min, min);*/

	printf("%d %d\n", *min, *max);
	printf("%p %p\n", min, max);

	return 0;}
