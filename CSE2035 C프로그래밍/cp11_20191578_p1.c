#include <stdio.h>
#include <string.h>
void split_string(char* str, char* string_1, char* string_2);

int main(void) {
	char string[51];
	char string_1[51], string_2[51];
	printf("input str : ");
	fgets(string, sizeof(string), stdin);
	split_string(string, string_1, string_2);
	string[strlen(string) - 1] = NULL;
	printf("[%s] -> [%s] [%s]\n", string, string_1, string_2);
	return 0;
}

void split_string(char* str, char* string_1, char* string_2) {
	int n = (strlen(str) - 1) / 2;
	int m = strlen(str) - 1 - n;
	strcpy(string_1, str);
	for (int i = n; i < strlen(str) - 1; i++)
		string_1[i] = NULL;

	strcpy(string_2, str);
	for (int i = n; i < strlen(str) - 1; i++) {
		string_2[i - n] = string_2[i];
	}

	for (int i = m; i < strlen(str) - 1; i++)
		string_2[i] = NULL;
}