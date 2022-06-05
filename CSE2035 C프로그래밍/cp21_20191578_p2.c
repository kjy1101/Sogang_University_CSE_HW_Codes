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
void DeleteNodeAtFront();
void DeleteNodeAtBack();
void PrintList();
void Free();

int main(void){
	InsertNodeAtFront('n');
	InsertNodeAtFront('e');
	InsertNodeAtFront('p');
	InsertNodeAtBack('l');
	InsertNodeAtFront('o');
	InsertNodeAtBack('a');
	InsertNodeAtBack('b');

	PrintList();

	DeleteNodeAtFront();
	DeleteNodeAtBack();
	DeleteNodeAtBack();
	DeleteNodeAtBack();

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

void DeleteNodeAtFront(){
	NODE *ptr;
	ptr=head;
	head=head->link;
	free(ptr);
}

void DeleteNodeAtBack(){
	NODE *pPrev, *pCur;
	pCur=pPrev=head;

	while(pCur->link!=NULL){
		pPrev=pCur;
		pCur=pCur->link;
	}
	pPrev->link=pCur->link;
	free(pCur);
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
