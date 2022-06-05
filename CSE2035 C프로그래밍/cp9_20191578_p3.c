#include <stdio.h>
#include <stdlib.h>
int max(int a, int b);
void swap(char *A, int *n, char *B, int *m);

int main(void){
	int n,m;
	char *A, *B, *answer;
	int **arr;
	scanf("%d %d", &n, &m);
	A=(char*)malloc((n+1)*sizeof(char));
	B=(char*)malloc((m+1)*sizeof(char));
	answer=(char*)malloc(20*sizeof(char));
	scanf("%s", A);
	scanf("%s", B);
	if(n<m) swap(A,&n,B,&m);

	arr=(int**)calloc(n+1,sizeof(int*));
	for(int i=0;i<n+1;i++)
		*(arr+i)=(int*)calloc(m+1,sizeof(int));

	int result=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(*(A+i-1)==*(B+j-1)){
				*(*(arr+i)+j)=*(*(arr+i-1)+j-1)+1;
				result=max(*(*(arr+i)+j), result);}
				//printf("result: %d\n",result);}
			else
				*(*(arr+i)+j)=0;}}
			//printf("arr[%d][%d]: %d\n",i,j,arr[i][j]);}}

	/*for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++)
			printf("%d ", *(*(arr+i)+j));
		printf("\n");}*/


	int index1,index2;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(*(*(arr+i)+j)==result){
				index1=i-1;
				index2=j-1;
				break;}}}
//	printf("index1: %d\n", index1);
//	printf("index2: %d\n", index2);
	int temp1=index1, temp2=index2;
	int index3, index4;
	while(*(*(arr+temp1)+temp2)>0){
		if(*(*(arr+temp1)+temp2)==1){
			index3=temp1-1;
			index4=temp2-1;}
		temp1--;temp2--;}

//	printf("index3: %d\n", index3);
//	printf("index4: %d\n", index4);

	int k=0;
	for(int i=index4;i<=index2;i++){
		*(answer+k)=*(B+i);
		k++;}

	if(result==1)
		*answer=*(B+index2-1);

	printf("Longest Common Substring = %s\n", answer);


	return 0;}

int max(int a, int b){
	if(a>=b) return a;
	else return b;}

void swap(char *A, int *n, char *B, int *m){
	char *temp;
	temp=(char*)malloc((*n+1)*sizeof(char));

	for(int i=0;i<*n+1;i++)
		*(temp+i)=*(A+i);

	A=realloc(A,(*m+1)*sizeof(char));

	for(int i=0;i<*m+1;i++)
		*(A+i)=*(B+i);

	B=realloc(B,(*n+1)*sizeof(char));

	for(int i=0;i<*n+1;i++)
		*(B+i)=*(temp+i);

	int temp1;
	temp1=*n;
	*n=*m;
	*m=temp1;}
