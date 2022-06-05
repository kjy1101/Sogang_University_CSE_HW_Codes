#include <stdio.h>
#include <stdlib.h>

float Area(int*, int*, int*, int*, int*, int*, float*);

int main(void)
{
int x1, y1, x2, y2, x3, y3;
float result;

scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
printf("%.2f\n",  Area(&x1, &y1, &x2, &y2, &x3, &y3, &result));

return 0;
}

float Area(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, float *result)
{
int A;
A = *x1**y2 + *x2**y3 + *x3**y1 - *x2**y1 - *x3**y2 - *x1**y3;
*result = 0.5 * abs(A);
return *result;
}
