#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n,m;
	char *n_num, *m_num, *result;
	char *num, *mum;
	char *final_n, *final_m;
	scanf("%d %d", &n, &m);
	n_num=malloc(n*sizeof(char));
	m_num=malloc(m*sizeof(char));
	int max=n;
	if(m>n) max=m;
	num=malloc(max*sizeof(char));
	mum=malloc(max*sizeof(char));
	final_n=malloc(max*sizeof(char));
	final_m=malloc(max*sizeof(char));
	result=malloc((max+1)*sizeof(char));
	scanf("%s", n_num);
	scanf("%s", m_num);
	int i,k;
	int sum=0, carry=0;
	if(n>=m){
		k=0;
		for(i=m-1;i>=0;i--){
			mum[k]=m_num[i];
			k++;}
		for(i=m;i<n;i++)
			mum[i]='0';
		k=0;
		for(i=max-1;i>=0;i--){
			final_m[k]=mum[i];
			k++;}
		//printf("%s\n", n_num);
		//printf("%s\n", final_m);

		for(i=max-1;i>=0;i--){
			sum=n_num[i]-'0'+final_m[i]-'0'+carry;
			carry=sum/10;
			sum%=10;
			result[i+1]=sum+'0';}
		result[0]=carry+'0';
		for(i=0;result[i]=='0';i++);
		printf("%s\n", result+i);
	}
	else{
		k=0;
		for(i=n-1;i>=0;i--){
			num[k]=n_num[i];
			k++;}
		for(i=n;i<m;i++)
			num[i]='0';
		k=0;
		for(i=max-1;i>=0;i--){
			final_n[k]=num[i];
			k++;}
		//printf("%s\n", final_n);
		//printf("%s\n", m_num);

		for(i=max-1;i>=0;i--){
			sum=final_n[i]-'0'+m_num[i]-'0'+carry;
			carry=sum/10;
			sum%=10;
			result[i+1]=sum+'0';}
		result[0]=carry+'0';
		for(i=0;result[i]=='0';i++);
		printf("%s\n", result+i);
	}
	free(n_num);
	free(m_num);
	free(num);
	free(mum);
	free(final_n);
	free(final_m);
	free(result);

	return 0;}
