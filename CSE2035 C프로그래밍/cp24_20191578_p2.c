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
int DequeuePrint(QUEUE* pQueue, char* dataOut);

int main(void) {
	char command[10];
	QUEUE* pQueue;
	pQueue = (QUEUE*)malloc(sizeof(QUEUE));
	pQueue->front = NULL;
	pQueue->count = 0;
	pQueue->rear = NULL;
	int value;
	int dv = 1;
	char dataOut[10];
	while (1) {
		printf(">> ");
		scanf("%s", command);
		value = CheckCommand(command);
		dv = 1;
		if (value == 1) {
			EnqueueCommand(pQueue, command);
			if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0) break;
			else if (strcmp(command, "history") == 0 || strcmp(command, "h") == 0) {
				while (dv == 1) {
					dv = DequeuePrint(pQueue, dataOut);
					printf("%s\n", dataOut);
				}
			}
		}
		else {
			printf("[Invalid]\n");
		}
	}
	return 0;
}

int CheckCommand(char* command) {
	int k = 0;
	if (strcmp(command, "help") == 0) k = 1;
	else if (strcmp(command, "dir") == 0) k = 1;
	else if (strcmp(command, "mkdir") == 0) k = 1;
	else if (strcmp(command, "cd") == 0) k = 1;
	else if (strcmp(command, "history") == 0) k = 1;
	else if (strcmp(command, "h") == 0) k = 1;
	else if (strcmp(command, "quit") == 0) k = 1;
	else if (strcmp(command, "q") == 0) k = 1;
	return k;
}

void EnqueueCommand(QUEUE* pQueue, char* dataIn) {
	if (strcmp(dataIn, "history") == 0 || strcmp(dataIn, "h") == 0) {

	}
	else if (strcmp(dataIn, "quit") == 0 || strcmp(dataIn, "q") == 0) {
		QUEUE_NODE* pre, * curr;
		curr = pQueue->front;
		while (curr->next != NULL) {
			pre = curr;
			curr = curr->next;
			free(pre);
		}
	}
	else {
		QUEUE_NODE* newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
		strcpy(newnode->command, dataIn);
		newnode->next = NULL;
		if (pQueue->count == 0) {
			pQueue->front = newnode;
			pQueue->rear = newnode;
		}
		else {
			pQueue->rear->next = newnode;
			pQueue->rear = newnode;
		}
		pQueue->count++;
		printf("[Valid] %s\n", newnode->command);
	}
}

int DequeuePrint(QUEUE* pQueue, char* dataOut) {
	QUEUE_NODE* deq;
	deq = pQueue->front;
	strcpy(dataOut, deq->command);
	pQueue->front = pQueue->front->next;
	pQueue->count--;
	free(deq);
	if (pQueue->count > 0) return 1;
	else return 0;
}