#include <stdio.h>
#include <stdlib.h>
typedef struct node* nptr;
typedef struct{
	int count;
	nptr link;
} STACK;

typedef struct node{
	char data;
	nptr link;
} STACK_NODE;

void Push(STACK*, char);
int Pop(STACK*);
//void PrintAll(STACK);

int main(void){
	STACK *pStack;
	pStack=(STACK*)malloc(sizeof(STACK));
	pStack->count=0;
	char input[100];
	int i=0,j=0;
	int success=0;
	scanf("%s", input);
	while(input[i]!='\0'){
		if(input[i]=='('||input[i]=='{'||input[i]=='['){
			Push(pStack, input[i]); j++;
		}
		else if(input[i]==')'||input[i]=='}'||input[i]==']'){
			if(pStack->count>0){
				success=Pop(pStack); j++;
			}
			else{
				success=0;
				j++;
				break;
			}
		}
		i++;
	}
	if(pStack->count==0){
		if(success==1||j==0) printf("Matched Parentheses!\n");
		else printf("Unmatched Parentheses!\n");
	}
	else{
		printf("Unmatched Parentheses!\n");
	}
	return 0;}

void Push(STACK* stack, char c){
	STACK_NODE *node;
	node=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	node->data=c;
	node->link=stack->link;
	stack->link=node;
	stack->count++;
}

int Pop(STACK* stack){
	STACK_NODE *node;
	node=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	node=stack->link;
	stack->link=stack->link->link;
	stack->count--;
	free(node);
	return 1;
}

/*void PrintAll(STACK stack){
	STACK_NODE *curr;
	curr=(STACK_NODE*)malloc(sizeof(STACK_NODE));
	curr->link=stack.link;
	while(curr->link!=NULL){
		curr=curr->link;
		printf("%c ", curr->data);
	}
	printf("\n");
	printf("Stack Level: %d\n", stack.count);
}*/
