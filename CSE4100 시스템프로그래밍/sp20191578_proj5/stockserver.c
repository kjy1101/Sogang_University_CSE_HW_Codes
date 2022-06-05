/* 
 * echoserveri.c - An iterative echo server 
 */ 
/* $begin echoserverimain */
#include "csapp.h"
#define BUFMAXSIZE 1000

typedef struct item{
	int ID;
	int left_stock;
	int price;
	int readcnt;
	sem_t mutex;
	struct item* left;
	struct item* right;
}Item;

Item* root;
char buff[BUFMAXSIZE];

Item* insert(Item* root, Item item);
Item* search(Item* item, int ID);
void print(Item* root, int connfd);
void file_print(Item* root);
void echo(int connfd);
void function(int connfd);
int find_ID_num(char *buf, int cmd, int len, int bs);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    char client_hostname[MAXLINE], client_port[MAXLINE];

	fd_set master;
	fd_set read_fds;
	int fdmax;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

	FILE *fp = fopen("stock.txt", "r");
	if(fp==NULL){
		printf("No input file\n");
		exit(1);
	}
	while(1){
		Item item;
		fscanf(fp, "%d %d %d", &item.ID, &item.left_stock, &item.price);
		if(feof(fp)) break;
		//printf("ID:%d, left_stock:%d, price:%d\n", item.ID, item.left_stock, item.price);
		root = insert(root, item);
	}
	//print(root);

    listenfd = Open_listenfd(argv[1]);
	FD_SET(listenfd, &master);
	fdmax = listenfd;

    while (1) {
		read_fds = master;
		Select(fdmax+1, &read_fds, NULL, NULL, NULL);
		for(int i=0;i<=fdmax;i++){
			if(FD_ISSET(i, &read_fds)){
				if(i==listenfd){
					clientlen = sizeof(struct sockaddr_storage); 
					connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        			Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
					FD_SET(connfd, &master);
					if(connfd > fdmax) fdmax = connfd;
        			printf("Connected to (%s, %s)\n", client_hostname, client_port);
				}else{
					function(i);
					close(i);
					FD_CLR(i, &master);
					FILE *ofp = fopen("stock.txt", "w");
					file_print(root);
					fprintf(ofp, "%s", buff);
					fclose(ofp);
					for(unsigned int i=0;i<strlen(buff);i++) buff[i]='\0';
				}
			}
		}

		/*clientlen = sizeof(struct sockaddr_storage); 
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
		//echo(connfd);
		function(connfd);
		Close(connfd);*/
    }
    exit(0);
}
/* $end echoserverimain */

Item* insert(Item* root, Item item){
	if(root == NULL){
		root = (Item*)malloc(sizeof(Item));
		root->right = root->left = NULL;
		root->ID = item.ID;
		root->left_stock = item.left_stock;
		root->price = item.price;
		root->readcnt = item.readcnt;
		return root;
	}else{
		if(item.ID < root->ID){
			root->left = insert(root->left, item);
		}
		else{
			root->right = insert(root->right, item);
		}
	}
	return root;
}

void print(Item* root, int connfd){
	if(root==NULL) return;
		char buf[30];
		sprintf(buf, "%d %d %d\n", root->ID, root->left_stock, root->price);
		//strcat(buff, buf);
		Rio_writen(connfd, buf, strlen(buf));
		print(root->left, connfd);
		print(root->right, connfd);
}

void file_print(Item* root){
	if(root==NULL) return;
		char buf[30];
		sprintf(buf, "%d %d %d\n", root->ID, root->left_stock, root->price);
		strcat(buff, buf);
		file_print(root->left);
		file_print(root->right);
}

Item* search(Item* item, int ID){
	if(!item) return NULL;
	if(ID == item->ID) return item;
	else if(ID > item->ID) search(item->right, ID);
	else search(item->left, ID);
}


int find_ID_num(char *buf, int cmd, int len, int bs){
	char temp[5], temp2[10];
	int j=0,k=0;
	int result;
	for(int i=4+bs;i<len;i++){
		if(buf[i]==' ') break;
		temp[j++] = buf[i];
	}
	temp[j]='\0';
	if(cmd==0){
		/* find ID */
		result = strtol(temp, NULL, 10);
		//printf("result_id: %d\n", result);
		return result;
	}
	/* find num */
	
	for(int i=j+4+bs;i<len;i++){
		temp2[k++] = buf[i];
	}
	temp2[k]='\0';
	result = strtol(temp2, NULL, 10);
	//printf("result_num: %d\n", result);
	return result;
}


void function(int connfd) 
{
    int n; 
    char buf[MAXLINE]; 
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
		printf("server received %d bytes\n", n);
		Rio_writen(connfd, buf, n);
		if(buf[0] == 'b'){
			/* buy */
			int ID = find_ID_num(buf, 0, n, 0);
			int num = find_ID_num(buf, 1, n, 0);
			//printf("ID: %d, num: %d\n", ID, num);
			Item *target = search(root, ID);
			if(target != NULL){
				//printf("target->ID: %d\n", target->ID);
				//printf("target->left_stock: %d\n", target->left_stock);
				//printf("target->price: %d\n", target->price);
				if(target->left_stock >= num){
					target->left_stock -= num;
					Rio_writen(connfd, "[buy] success\n", 14);
				}else{
					Rio_writen(connfd, "Not enough left stock\n", 22);
				}
			}else{
				//printf("No stock\n");
				Rio_writen(connfd, "Not enough left stock\n", 22);
			}
			//Rio_writen(connfd, "response-buy\n", 13);
		}else if(buf[0]=='e'){
			/* exit */
		}else{
			if(buf[1] == 'h'){
				/* show */
				print(root, connfd);
				//strcat(buff, "\n");
				//Rio_writen(connfd, buff, strlen(buff));
				Rio_writen(connfd, "0\n", 2);
				//for(unsigned int i=0;i<strlen(buff);i++) buff[i]='\0';
			}else{
				/* sell */
				int ID = find_ID_num(buf, 0, n, 1);
				int num = find_ID_num(buf, 1, n, 1);
				Item *target = search(root, ID);
				if(target != NULL){
					//printf("target->ID: %d\n", target->ID);
					//printf("target->left_stock: %d\n", target->left_stock);
					//printf("target->price: %d\n", target->price);
					target->left_stock += num;
					Rio_writen(connfd, "[sell] success\n", 15);
				}else{
					//printf("new stock\n");
					Item item;
					item.ID = ID;
					item.left_stock = num;
					item.price = 10000;
					root = insert(root, item);
					//printf("left_stock: %d\n", item.left_stock);
					//printf("num: %d\n", num);
					Rio_writen(connfd, "[sell] success\n", 15);
				}
				//Rio_writen(connfd, "response-sell\n", 14);
			}
		}
    }
}


