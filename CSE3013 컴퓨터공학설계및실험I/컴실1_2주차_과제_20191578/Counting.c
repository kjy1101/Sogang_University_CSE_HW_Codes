//array[page]의 숫자 개수를 세는 함수
#include "Header.h"

void Counting(int* arr1, int *arr2, int n){
	//arr1은 개수배열, arr2은 페이지배열
	int r;
	for(int i=0;i<n;i++){
		if(arr2[i]<10){
		//한자릿수면 그냥 +1
			arr1[i+1]++;
		}
		else{
		//두자릿수 이상이면 10으로 나눠야함(나머지 사용)
			while(1){
				r=arr2[i]%10;
				arr1[r]++;
				arr2[i]=arr2[i]/10;
				if(arr2[i]==0) break;
			}
		}
	}
}
