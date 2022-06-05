#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node *link;
} NODE;
typedef NODE* nptr;

void Insert(nptr* head, int data, int index);
void PrintAll(nptr head);
void Free(nptr head);

int main(void){
	int A[10]={3,9,8,2,5,10,7,1,4,6};
	nptr head;
	head=(NODE*)malloc(sizeof(NODE));
	head->link=NULL;

	Insert(&head, A[0],0);
	PrintAll(head);

	Insert(&head, A[1],0);
	PrintAll(head);

	Insert(&head, A[2],1);
	PrintAll(head);

	Insert(&head, A[3],2);
	PrintAll(head);

	Insert(&head, A[4],0);
	PrintAll(head);

	Insert(&head, A[5],1);
	PrintAll(head);

	Insert(&head, A[6],10);
	PrintAll(head);

	Insert(&head, A[7],4);
	PrintAll(head);

	Insert(&head, A[8],-1);
	PrintAll(head);

	Insert(&head, A[9],3);
	PrintAll(head);

	Free(head);
	return 0;}

void Insert(nptr* head, int data, int index){
	NODE* newnode=(NODE*)malloc(sizeof(NODE));
	newnode->data=data;

	nptr curr=(NODE*)malloc(sizeof(NODE));
	curr=*head;
	int i=0;
	if(index==0){
		newnode->link=(*head)->link;
		(*head)->link=newnode;
	}
	else if(index<0||index>=10){
		while(curr->link!=NULL){
			curr=curr->link;
		}
		curr->link=newnode;
		newnode->link=NULL;
	}
	else{
		while(curr->link!=NULL){
			if(i>=index) break;
			curr=curr->link;
			i++;
		}

		newnode->link=curr->link;
		curr->link=newnode;
	}
}


void PrintAll(nptr head){
	nptr curr=(NODE*)malloc(sizeof(NODE));
	curr=head;
	while(curr->link!=NULL){
		curr=curr->link;
		printf("%d ", curr->data);
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
