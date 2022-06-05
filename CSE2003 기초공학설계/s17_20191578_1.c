#include <stdio.h>

int palindrome(int num, int digit);

int main(void){
	int num, digit=1, result;
	printf("Input: ");
	scanf("%d", &num);

	if (num<0) {
		printf("Input number cannot be negative.\n");
		return 0;
	}
	if (num == 0)
		printf("%d is a palindrome number.\n", num);
	else{
		result = palindrome(num, digit);
		if (result == 1)
			printf("%d is a palindrome number.\n", num);
		else
			printf("%d is not a palindrome number.\n", num);}
//	printf("\nResult: %d\n", result);
	return 0;}

int palindrome(int num, int digit){
	int i, maxdigit, a, b;
//	printf("\npalindrome started\n");
//	printf("digit: %d\n", digit);
//	printf("number: %d\n", num);

	for(i=1;;i*=10){
		if (i>num){
			maxdigit = i/10;
			break;}}

	a = (num / (maxdigit/digit))%10;
	b = (num % (digit * 10)) / digit;

//	printf("a=%d, b=%d\n", a, b);
	if (a==b){
		if (maxdigit/digit == digit)
			return 1;
		if (maxdigit/digit == digit*10){
			return 1;
		}
		else {
			return palindrome(num, digit*10);
		}
	}
	else {
		return 0;
	}
}
