#include <stdio.h>

int main(void){
int n1, n2;
printf("Enter 2 numbers: ");
scanf("%d %d", &n1, &n2);
int a1, a2, a3, b1, b2, b3, total;
a1 = n1 / 100;
a2 = (n1 % 100) / 10;
a3 = n1 % 10;
b1 = n2 / 100;
b2 = (n2 % 100) / 10;
b3 = n2 % 10;
total = 0;
if (a3 + b3 >= 10)
	{total += 1;
	a2 += 1;}
if (a2 + b2 >= 10)
	{total += 1;
	a1 += 1;}
if (a1 + b1 >= 10)
	total += 1;
printf("%d carry operations\n", total);
return 0;
}	
