#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
	char data;
	nptr link;
} NODE;

nptr head=NULL;
nptr tail=NULL;
nptr last=NULL;

void InsertNodeAtFront(char);
void InsertNodeAtBack(char);
void PrintList();
void Free();

int main(void){
	InsertNodeAtFront('p');
	InsertNodeAtFront('p');
	InsertNodeAtFront('a');
	InsertNodeAtBack('l');
	InsertNodeAtBack('e');

	PrintList();
	Free();

	return 0;}

void InsertNodeAtFront(char c){
	NODE* newnode;
	newnode=(NODE*)malloc(sizeof(NODE));
	newnode->link=NULL;
	newnode->data=c;
	if(head==NULL){
		head=newnode;
		tail=newnode;
	}
	else{
		head=newnode;
		newnode->link=tail;
		tail=head;
	}
}

void InsertNodeAtBack(char c){
	nptr curr;
	curr=head;
	while(1){
		if(curr->link==NULL) break;
		curr=curr->link;
	}
	last=curr;
	NODE* newnode;
	newnode=(NODE*)malloc(sizeof(NODE));
	newnode->link=NULL;
	newnode->data=c;
	if(head==NULL){
		head=newnode;
		last=newnode;
	}
	else{
		last->link=newnode;
		last=newnode;
	}
}

void PrintList(){
	nptr curr;
	curr=head;
	while(curr->link!=NULL){
		printf("%c", curr->data);
		curr=curr->link;
	}
	printf("%c", curr->data);
	printf("\n");
}

void Free(){
	nptr target=head;
	nptr temp=target;
	while(target!=NULL){
		temp=temp->link;
		free(target);
		target=temp;
	}
}
