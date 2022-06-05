#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node *link;
} NODE;
typedef NODE* nptr;

void Insert(nptr* head, int data);
void Sort(nptr* head);
void PrintAll(nptr head);

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
	node->link=NULL;
	PrintAll(head);
	Sort(&head);
	PrintAll(head);

	return 0;}

void Insert(nptr* head, int data){
	(*head)->link=(NODE*)malloc(sizeof(NODE));
	(*head)->data=data;
}

void Sort(nptr* head){
	nptr node=*head;
	for(int i=9;i>0;i--){
		for(int j=0;j<i;j++){
			if((node->data)>((node->link)->data)){
				int temp=(node->data);
				(node->data)=((node->link)->data);
				((node->link)->data)=temp;
			}
			node=node->link;
		}
		node=*head;
	}
}

void PrintAll(nptr head){
	nptr curr=(NODE*)malloc(sizeof(NODE));
	curr=head;
	while(curr->link!=NULL){
		printf("%d ", curr->data);
		curr=curr->link;
	}
	printf("\n");
}
