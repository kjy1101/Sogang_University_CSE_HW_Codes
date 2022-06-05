#include <stdio.h>
#include <stdlib.h>
typedef struct node* nptr;
typedef struct node{
	int data;
	struct node *link;
} NODE;

void Insert(NODE**, int);
void Delete(NODE**);
void PrintAll(NODE*);
void Free(NODE*);

int main(void){
	int A[10]={3,9,8,2,5,10,7,1,4,6};

	NODE *head;
	head=(NODE*)malloc(sizeof(NODE));
	head->link=NULL;

	NODE *node;
	node=(NODE*)malloc(sizeof(NODE));
	node=head;

	for(int i=0;i<10;i++){
		Insert(&node, A[i]);
		node=node->link;
	}

	node->link=NULL;
	PrintAll(head);

	for(int i=0;i<10;i++){
		Delete(&head);
		PrintAll(head);
	}

	Free(head);

	return 0;}

void Insert(NODE** node, int a){
	(*node)->link=(NODE*)malloc(sizeof(NODE));
	(*node)->data=a;
}

void Delete(NODE** head){
	NODE *ptr;
	ptr=(*head);
	(*head)=(*head)->link;
	free(ptr);
}

void PrintAll(NODE* head){
	NODE *curr;
	curr=(NODE*)malloc(sizeof(NODE));
	curr=head;
	int i=0;
	while(1){
		if(curr->link==NULL) break;
		printf("%d ", curr->data);
		curr=curr->link;
		i++;
	}
	if(i==0) printf("Empty");
	printf("\n");
}

void Free(NODE* head){
	NODE *target=head;
	NODE *temp=target;
	while(target!=NULL){
		temp=temp->link;
		free(target);
		target=temp;
	}
}
