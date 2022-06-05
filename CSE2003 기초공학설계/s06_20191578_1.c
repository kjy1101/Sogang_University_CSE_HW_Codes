#include <stdio.h>

float find_x(int, int, int, int);
float find_y(int, int, float);

int main(void)
{
int a;
int b;
int c;
int d;
float first;
float second;

printf("1st equation: y = ax - b, input 'a' and 'b'\n");
printf("a = ");
scanf("%d", &a);
printf("b = ");
scanf("%d", &b);

printf("2nd equation: y = cx - d, input 'c' and 'd'\n");
printf("c = ");
scanf("%d", &c);
printf("d = ");
scanf("%d", &d);

first = find_x(a, b, c, d);
second = find_y(a, b, first);

printf("result:\nx is %f\ny is %f\n", first, second);

return 0;
}

float find_x(int a, int b, int c, int d)
{
float x;
x = (float)(b - d) / (float)(a - c);
return x;
}

float find_y(int a, int b, float x)
{
float y;
y = a*x - b;
return y;
}
