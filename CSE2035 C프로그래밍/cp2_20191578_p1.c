#include <stdio.h>
void sort4(int *a, int *b, int *c, int *d);

int main(void){
	int a,b,c,d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	sort4(&a,&b,&c,&d);
	printf("%d %d %d %d\n", a, b, c, d);
	return 0;}

void sort4(int *a, int *b, int *c, int *d){
	int array[4];
	array[0]=*a;
	array[1]=*b;
	array[2]=*c;
	array[3]=*d;
	for(int j=0;j<3;j++){

	for(int i=0;i<3-j;i++){
		if(array[i]>array[i+1]){
			int temp;
			temp=array[i];
			array[i]=array[i+1];
			array[i+1]=temp;
		}
	}}
	*a=array[0];
	*b=array[1];
	*c=array[2];
	*d=array[3];

}
