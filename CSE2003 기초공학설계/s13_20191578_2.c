#include <stdio.h>

int main(void){
int n;
int remain;

printf("Input: ");
scanf("%d", &n);
remain = n % 2;

(remain == 0) ? printf("%d is even number.\n", n) : printf("%d is odd number.\n", n);

return 0;
}
