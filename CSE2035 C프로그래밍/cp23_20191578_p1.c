#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} QUEUE_NODE;

typedef struct {
	QUEUE_NODE* front;
	int count;
	QUEUE_NODE* rear;
} QUEUE;

void Exit(QUEUE*);
void Enqueue(QUEUE*);
void PrintAll(QUEUE);

int main(void) {
	int select;
	QUEUE* queue;
	queue = (QUEUE*)malloc(sizeof(QUEUE));
	queue->count = 0;
	queue->front = NULL;
	queue->rear = NULL;
	int flag = 0;
	printf("****** Menu ******\n");
	printf("* 0 : Exit	 *\n");
	printf("* 1 : Enqueue	 *\n");
	printf("* 2 : -------	 *\n");
	printf("* 3 : PrintAll	 *\n");
	printf("******************\n");
	
	while (flag!=1) {
		printf("Select > ");
		scanf("%d", &select);
		switch (select) {
			case 0:
				flag = 1;
				break;
			case 1:
				Enqueue(queue);
				break;
			case 3:
				PrintAll(*queue);
				break;
		}
	}
	Exit(queue);
	return 0;
}

void Exit(QUEUE* queue) {
	if (queue->count != 0) {
		QUEUE_NODE* pre;
		QUEUE_NODE* cur;
		cur = queue->front;
		while (cur != NULL) {
			pre = cur;
			cur = cur->next;
			free(pre);
		}
	}
	free(queue);
}
void Enqueue(QUEUE* queue) {
	int input;
	QUEUE_NODE* newnode;
	newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	printf("Input Data > ");
	scanf("%d", &input);
	newnode->data = input;
	if (queue->count == 0) {
		//처음
		//front가 newnode를 가리킨다(머리)
		queue->front = newnode;
	}
	else {
		//두번째
		//직전에 추가한 노드의 next가 이번에 추가한 newnode를 가리키게 한다
		queue->rear->next = newnode;
	}
	//rear가 newnode를 가리킨다(꼬리)
	queue->rear = newnode;
	queue->count++;
}

void PrintAll(QUEUE queue) {
	QUEUE_NODE *cur;
	cur = queue.front;
	for (int i = 0; i < queue.count; i++) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
	printf("Queue level : %d\n", queue.count);
}