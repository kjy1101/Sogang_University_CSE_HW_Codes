#include <stdio.h>
#include <stdlib.h>
typedef struct node *sptr;
typedef struct{
	int count;
	sptr link;
} STACK;
typedef struct node{
	int data;
	sptr link;
} STACK_NODE;

void Exit(STACK*);
void Push(STACK*);
void Pop(STACK*);
void PrintAll(STACK);

int main(void){
	STACK *stack;
	stack=(STACK*)malloc(sizeof(STACK));
	stack->count=0;
	stack->link=NULL;
	
	printf("****** Menu ******\n");
	printf("* 0 : Exit       *\n");
	printf("* 1 : Push       *\n");
	printf("* 2 : Pop        *\n");
	printf("* 3 : Print All  *\n");
	printf("******************\n");
	int order;
	while(1){
		printf("Select > ");
		scanf("%d", &order);
		switch(order){
			case 0 : 
				Exit(stack);
				break;
			case 1 : 
				Push(stack);
				break;
			case 2 : 
				Pop(stack);
				break;
			case 3 : 
				PrintAll(*stack);
				break;
		}
		if(order==0) break;
	}
	return 0;}

void Exit(STACK* stack){
	sptr target=stack->link;
	sptr temp=target;
	while(target->link!=NULL){
		temp=temp->link;
		free(target);
		target=temp;
	}
}

void Push(STACK* stack){
	STACK_NODE* node;
	node=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	printf("Input Data > ");
	scanf("%d", &(node->data));
	node->link=stack->link;
	stack->link=node;
	stack->count++;

}

void Pop(STACK* stack){
	STACK_NODE *node;
	node=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	int dataOut=stack->link->data;
	printf("Pop %d\n", dataOut);
	node=stack->link;
	stack->link=(stack->link)->link;
	stack->count--;
	free(node);
}

void PrintAll(STACK stack){
	STACK_NODE *curr;
	curr=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	curr->link=stack.link;
	int array[100];
	int i=0;
	if(stack.count==0){
		printf("Stack is Empty!\n");
	}
	else{
		while(curr->link!=NULL){
			curr=curr->link;
			array[i]=curr->data;
			i++;
//			printf("%d ", curr->data);
		}
		i--;
		for(int j=i;j>=0;j--){
			printf("%d ", array[j]);
		}
		printf("\nStack Level : %d\n", stack.count);
	}
}
