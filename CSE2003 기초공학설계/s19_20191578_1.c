#include <stdio.h>

double string_double(char string[11]); //마침표 때문에 자리수 +1
float power(float a, float b);

int main(void){
	char string[11]={0};

	for(int i=0;i<11;i++){
		scanf("%c", &string[i]);
		if (string[i] == '\n')
			break;}

	printf("Result: %.6lf\n", string_double(string));
//	string_double(string);

	return 0;}


double string_double(char string[11]){
	double n=0;
	int index=0;
	for(int i=0;i<11;i++){
		if (string[i] == '.')
			index = i;}
	if (index != 0){
		for(int i=4;i>=1;i--){
			if (string[index-i]-48 >= 0)
				n += (string[index-i]-48)*power(10, i-1);}
//				printf("%lf %f\n", (string[index-i]-48), power(10, i-1));}

//		printf("%c\n", string[index]);

		for(int i=1;i<=6;i++){
			if (string[index+i]-48 >= 0){
				n += (string[index+i]-48)*power(0.1, i);}}}
//				printf("%lf %f\n", (string[index+i]-48), power(0.1, i));}

	if (index == 0){
		for(int i=3;i>=0;i--){
			if (string[i]-48>=0)
				n += (string[i]-48)*power(10, 3-i);}}

	if (string[0] == '-')
		return -n;
	if (string[0] != '-')
		return n;}

float power(float a, float b){
	float result=1;
	for(int i=1;i<=b;i++){
		result = result * a;}
	return result;}




//	string[index-1]*1
//	string[i-2]*10
//	string[i-3]*100
//	string[i-4]*1000
//	string[i+1]*0.1
//	string[i+2]*0.01
//	string[i+3]*0.001
//	string[i+4]*0.0001
//	string[i+5]*0.00001
//	string[i+6]*0.000001
