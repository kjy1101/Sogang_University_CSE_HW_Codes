#include <stdio.h>
int find2or3(int a, int b, int i);

int main(void){
	int a, b, i, result;
	printf("Input first number: ");
	scanf("%d", &a);
	printf("Input second number: ");
	scanf("%d", &b);

	if ((a < 1) || (b < 1)){
		printf("Input is less than 1\n");}
	else{
		if (a > b)
			{int temp;
			temp = a;
			a = b;
			b = temp;}

		result = find2or3(a, b, i);

		printf("Result: %d\n", result);
		return 0;}}

int find2or3(int a, int b, int i)
	{int total=0;
		for (i=a;i<=b;i++)
			{if ((i%2==0) || (i%3==0))
				{total += i;}}
	return total;}
