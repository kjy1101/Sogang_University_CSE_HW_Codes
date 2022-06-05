#include <stdio.h>

int main(void) {
int birthday;

printf("Birthday : ");
scanf("%d", &birthday);

int year = birthday / 10000;
int month = birthday % 10000 / 100;
int date = birthday % 100;

printf("Your birthday is %d / %d / %d\n", year, month, date);

int inputyear;
printf("Year : ");
scanf("%d", &inputyear);
printf("In %d, your age is %d\n", inputyear, inputyear - year + 1);

return 0;
}
