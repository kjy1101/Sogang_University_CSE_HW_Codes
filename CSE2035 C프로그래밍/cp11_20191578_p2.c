#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strncpy(char* a, char* b, int n);
void initialization(char* a, int n);

int main(void) {
	char str[20];
	char* str1;

	printf("input str : ");
	gets(str);

	str1 = (char*)malloc((strlen(str) + 1) * sizeof(char));
	strcpy(str1, str);

	for (int i = 0; i < strlen(str1) + 1; i++) {
		initialization(str, strlen(str));
		my_strncpy(str, str1, i);
		printf("%s\n", str);
	}
	free(str1);
	return 0;
}

char* my_strncpy(char* a, char* b, int n) {
	for (int i = 0; i < n; i++)
		* (a + i) = *(b + i);
}
void initialization(char* a, int n) {
	for (int i = 0; i < n; i++)
		* (a + i) = '*';
}