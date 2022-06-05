#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char path[1001];
	char file[1001];
	char newpath[1001] = { 0 };
	printf("Path : ");
	gets(path);
	printf("File name : ");
	gets(file);

	strcpy(newpath, path);
	int index = 0;
	for (int i = strlen(newpath) - 1; i >= 0; i--) {
		if (newpath[i] == '/') {
			index = i + 1;
			break;
		}
	}

	int k = 0, end = 0;
	for (int i = index; i < index + strlen(file); i++) {
		newpath[i] = file[k];
		k++;
		end = i + 1;
	}
	if (end < strlen(newpath)) {
	for (int i = end; i < strlen(path); i++) {
		newpath[i] = NULL;
	}
}
	printf("New path : %s\n", newpath);

	return 0;
}