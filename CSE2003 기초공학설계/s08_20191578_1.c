#include <stdio.h>

void swap(float *x, float *y);

int main(void)
{
float num1;
float num2;

printf("Input two Number\n");
printf("	x : ");
scanf("%f", &num1);
printf("	y : ");
scanf("%f", &num2);
printf("------------------------------------------------\n");
printf("Before : x [%f] y [%f]\n", num1, num2);
printf("------------------------------------------------\n");

swap(&num1, &num2);
printf("After  : x [%f] y [%f]\n", num1, num2);

return 0;
}

void swap(float *x, float *y)
{
float T;
T = *x;
*x = *y;
*y = T;
}
