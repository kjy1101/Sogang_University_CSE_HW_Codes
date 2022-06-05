#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
typedef struct node{
	int data;
	nptr link;
} NODE;

void Insert(nptr*, int);
void PrintAll(nptr);
void Free(nptr);

int main(void){
	int A[10]={3,9,8,2,5,10,7,1,4,6};

	nptr head=(NODE*)malloc(sizeof(NODE));
	head->link=NULL;

	nptr node=(NODE*)malloc(sizeof(NODE));
	node=head;

	for(int i=0;i<10;i++){
		Insert(&node, A[i]);
		node=node->link;
	}
	
	PrintAll(head);
	Free(head);

	return 0;}

void Insert(nptr* ptr, int a){
	(*ptr)->link=(NODE*)malloc(sizeof(NODE));
	(*ptr)->data=a;
}

void PrintAll(nptr head){
	nptr curr=(NODE*)malloc(sizeof(NODE));
	curr=head;
	while(1){
		if(curr->link==NULL) break;
		printf("%d ", curr->data);
		curr=curr->link;
	}
	printf("\n");
}

void Free(nptr head){
	nptr target=head;
	nptr temp=target;
	while(target!=NULL){
		temp=temp->link;
		free(target);
		target=temp;
	}
}
