#include <stdio.h>

int plus(int, int);
int main(void)
{
int number1;
int number2;
int value;

printf("Input first number: ");
scanf("%d", &number1);
printf("Input second number: ");
scanf("%d", &number2);

value = plus(number1, number2);

printf("%d + %d = %d\n", number1, number2, value);

return 0;
}

int plus(int number1, int number2)
{
int result;
result = number1 + number2;
return result;
}
