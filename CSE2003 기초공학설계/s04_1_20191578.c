#include <stdio.h>

int main(void) {

int price;
printf("Price : ");
scanf("%d", &price);

int payment3;
int payment6;

payment3 = price;
payment6 = price * 1.05 * 1.05 * 1.05;

printf("----------------output----------------\n");
printf("Month\t\t: %10d%10d\n", 3, 6);
printf("Payment\t\t: %10d%10d\n", payment3, payment6);
printf("--------------------------------------\n");
printf("Pay/month\t: %10.2f%10.2f\n", (float)payment3 / 3, (float)payment6/ 6);

return 0;
}
