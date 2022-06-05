#include <stdio.h>

float average_f(int, int, int, int);
float deviation_f(int, float);

int main(void)
{
int a;
int b;
int c;
int d;
float average;
float dev_a;
float dev_b;
float dev_c;
float dev_d;

printf("Enter the first number : ");
scanf("%d", &a);
printf("Enter the second number : ");
scanf("%d", &b);
printf("Enter the third number : ");
scanf("%d", &c);
printf("Enter the fourth number : ");
scanf("%d", &d);

average = average_f(a, b, c, d);
printf("******** average is %.2f ********\n", average);

dev_a = deviation_f(a, average);
dev_b = deviation_f(b, average);
dev_c = deviation_f(c, average);
dev_d = deviation_f(d, average);
printf("first number :		%10d  -- deviation :		%10.2f\n", a, dev_a);
printf("second number :		%10d  -- deviation :		%10.2f\n", b, dev_b);
printf("third number :		%10d  -- deviation :		%10.2f\n", c, dev_c);
printf("fourth number :		%10d  -- deviation :		%10.2f\n", d, dev_d);

return 0;
}

float average_f(int a, int b, int c, int d)
{
float value;
float result;

value = a + b + c + d;
result = value / 4;

return result;
}

float deviation_f(int x, float average)
{
float result;
result = x - average;
return result;
}
