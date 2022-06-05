#include <stdio.h>
int sqr(int);
int printOne(int);

int main(void)
{
int number;
int square;

printf("Input: ");
scanf("%d", &number);

square = sqr(number);

return 0;
}



int sqr(int number)
{
int result;
int print;

result = number * number;

print =  printOne(result);

return result;
}

int printOne(int result)
{
printf("Result: %d\n", result);}
