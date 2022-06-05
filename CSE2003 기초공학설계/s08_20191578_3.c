#include <stdio.h>

int x = 1;
int Fibonacci (int *y);

int main(void)
{
int x = 0;

printf("Fibo(2): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(3): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(4): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(5): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(6): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(7): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(8): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
printf("Fibo(9): %d,x=%d, &x=%x\n", Fibonacci(&x),x,&x);
//printf("Fibo(3): %d\n", Fibonacci(&x));
//printf("Fibo(4): %d\n", Fibonacci(&x));
//printf("Fibo(5): %d\n", Fibonacci(&x));
//printf("Fibo(6): %d\n", Fibonacci(&x));
//printf("Fibo(7): %d\n", Fibonacci(&x));
//printf("Fibo(8): %d\n", Fibonacci(&x));
//printf("Fibo(9): %d\n", Fibonacci(&x));

return 0;
}

int Fibonacci(int *y)
{
int temp = x;

printf("%x\n", &x);

x += *y;
*y = temp;
return x;
}
