#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
	char command[10];
	struct node* next;
} QUEUE_NODE;

typedef struct {
	QUEUE_NODE* front;
	int count;
	QUEUE_NODE* rear;
} QUEUE;

int CheckCommand(char* command);
void EnqueueCommand(QUEUE* pQueue, char* dataIn);

int main(void) {
	char command[10];
	QUEUE* pQueue;
	pQueue = (QUEUE*)malloc(sizeof(QUEUE));
	pQueue->front = NULL;
	pQueue->count = 0;
	pQueue->rear = NULL;
	int check;
	while (1) {
		printf(">>");
		scanf("%s", command);
		check = CheckCommand(command);
		if (check == 1) {
			//유효한 명령어일 때
			EnqueueCommand(pQueue, command);
		}
		else {
			printf("[Invalid]\n");
		}
	}

	return 0;
}

int CheckCommand(char* command) {
	if (strcmp("help", command) == 0) return 1;
	else if (strcmp("dir", command) == 0) return 1;
	else if (strcmp("mkdir", command) == 0) return 1;
	else if (strcmp("cd", command) == 0) return 1;
	else if (strcmp("history", command) == 0) return 1;
	else if (strcmp("h", command) == 0) return 1;
	else if (strcmp("quit", command) == 0) return 1;
	else if (strcmp("q", command) == 0) return 1;
	else return 0;
}

void EnqueueCommand(QUEUE* pQueue, char* dataIn) {
	if (strcmp("history", dataIn) == 0 || strcmp("h", dataIn) == 0) {
		//현재까지의 유효한 명령어 수를 출력
		printf("queue count = %d\n", pQueue->count);
	}
	else if (strcmp("quit", dataIn) == 0 || strcmp("q", dataIn) == 0) {
		//종료
		if (pQueue->count != 0) {
			QUEUE_NODE* pre;
			QUEUE_NODE* cur;
			cur = pQueue->front;
			while (cur != NULL) {
				pre = cur;
				cur = cur->next;
				free(pre);
			}
		}
		free(pQueue);
	}
	else {
		//카피해서 출력
		QUEUE_NODE* newnode;
		newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
		strcpy(newnode->command, dataIn);
		if (pQueue->count == 0) {
			pQueue->front = newnode;
		}
		else {
			pQueue->rear->next = newnode;
		}
		pQueue->rear = newnode;
		pQueue->count++;
		printf("[Valid] %s\n", pQueue->rear->command);
	}
}