#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	int data;
	struct node* next;
}QUEUE_NODE;
typedef struct {
	QUEUE_NODE* front;
	int count;
	QUEUE_NODE* rear;
} QUEUE;
void Exit(QUEUE*);
void Enqueue(QUEUE*);
void PrintAll(QUEUE);
void Dequeue(QUEUE*);

int main(void) {
	printf("****** Menu ******\n");
	printf("* 0 : Exit	 *\n");
	printf("* 1 : Enqueue	 *\n");
	printf("* 2 : Dequeue	 *\n");
	printf("* 3 : Print All	 *\n");
	printf("******************\n");
	int select;
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	queue->count = 0;
	queue->front = NULL;
	queue->rear = NULL;
	while (1) {
		printf("Select > ");
		scanf("%d", &select);
		if (select == 0) {
			Exit(queue);
			break;
		}
		else if (select == 1) {
			Enqueue(queue);
		}
		else if (select == 2) {
			Dequeue(queue);
		}
		else {
			PrintAll(*queue);
		}
	}
}

void Exit(QUEUE* queue) {
	QUEUE_NODE* pre, * cur;
	cur = queue->front;
	while (cur->next != NULL) {
		pre = cur;
		cur = cur->next;
		free(pre);
	}
	free(queue);
}
void Enqueue(QUEUE* queue) {
	int data;
	printf("Input Data > ");
	scanf("%d", &data);
	QUEUE_NODE* newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	newnode->data = data;
	newnode->next = NULL;
	if (queue->count == 0) {
		queue->front = newnode;
		queue->rear = newnode;
	}
	else {
		queue->rear->next = newnode;
		queue->rear = newnode;
	}
	queue->count++;
}
void PrintAll(QUEUE queue) {
	QUEUE_NODE* curr;
	curr = queue.front;
	while (curr->next != NULL) {
		printf("%d ", curr->data);
		curr = curr->next;
	}
	printf("%d\n", curr->data);
	printf("Queue Level : %d\n", queue.count);
}

void Dequeue(QUEUE* queue) {
	QUEUE_NODE* deq;
	int dataOut;
	deq = queue->front;
	dataOut = deq->data;
	queue->front = queue->front->next;
	printf("Dequeue %d\n", dataOut);
	queue->count--;
	free(deq);
}