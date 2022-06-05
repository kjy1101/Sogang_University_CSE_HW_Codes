#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _listPointer{
	int data;
	struct _listPointer *next;
	struct _listPointer *prev;
}_listPointer;
typedef _listPointer* listPointer;

void print_forward(listPointer list);
void print_reverse(listPointer list);

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("usage: ./mp1 input_filename\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("The input file does not exist.\n");
		exit(1);
	}

	listPointer head;
	head=NULL;

	FILE *outfile = fopen("mp1_result.txt", "w");

	char command[10]={0};
	int num=0;
	while(1){
		fscanf(fp, "%s", command);
		if(feof(fp)) break;
		if(strcmp(command, "INSERT")==0 || strcmp(command, "DELETE")==0)
			fscanf(fp, "%d", &num);

		if(strcmp(command, "INSERT")==0){
			if(head==NULL){
				head=malloc(sizeof(listPointer));
				head->data=num;
				head->next=head;
				head->prev=head;
			}
			else{
				listPointer newnode;
				newnode=malloc(sizeof(listPointer));
				newnode->data = num;

				listPointer curr=head;
				int flag=0;
				int c=0;
				while(1){
					c++;
					if(curr->data == num){
						flag=2;
						break;
					}
					else{
						if(curr->data > num){
								break;}
						if(curr->next==head){
							flag=1;
							break;
						}
					}
					curr=curr->next;
				}
				if(flag==0){
					newnode->prev = curr->prev;
					newnode->next = curr;
					curr->prev->next = newnode;
					curr->prev = newnode;
					if(c==1){
						listPointer temp;
						temp = head;
						head = newnode;
						newnode = head;			
					}
				}
				else if(flag==1){
					newnode->next = curr->next;
					curr->next->prev = newnode;
					curr->next = newnode;
					newnode->prev = curr;
				}
			}
		}
		else if(strcmp(command, "DELETE")==0){
			if(head!=NULL){
			listPointer curr;
			curr=head;
			int flag=0;
			int c=0;
			while(1){
				c++;
				if(curr->data == num) break;
				if(curr->next == head){
					flag=1;
					break;
				}
				curr=curr->next;
			}
			if(flag==0){
				if(c==1){
					//삭제할 노드가 head
					if(head->next != head){
						head=curr->next;}
					else{
						head=NULL;}
				}
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr);
			}
			}
		}
		else if(strcmp(command, "ASCEND")==0) print_forward(head);
		else if(strcmp(command, "DESCEND")==0) print_reverse(head);
	}
	fclose(fp);
	fclose(outfile);
	return 0;
}


void print_forward(listPointer list){
	listPointer curr;
	FILE *outfile;
	outfile = fopen("mp1_result.txt", "a");
	if(list){
		curr=list;
		while(1){
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->next;
			if(curr==list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}

void print_reverse(listPointer list){
	listPointer curr;
	FILE *outfile;
	outfile = fopen("mp1_result.txt", "a");
	if(list){
		curr = list->prev;
		while(curr!=list){
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		}
		fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}
