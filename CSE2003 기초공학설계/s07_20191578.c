#include <stdio.h>

void divideRemainder(int *a, int *b);

int main(void)
{
int a;
int b;

printf("Input two Number : ");
scanf("%d %d", &a, &b);
printf("--------------------------------\n");

divideRemainder(&a, &b);
printf("OUTPUT : divide [%d] remainder [%d]\n", a, b);

return 0;
}


void divideRemainder(int *a, int *b)
{
int T;
T = *a;
*a = *a / *b;
*b = T % *b;
}
