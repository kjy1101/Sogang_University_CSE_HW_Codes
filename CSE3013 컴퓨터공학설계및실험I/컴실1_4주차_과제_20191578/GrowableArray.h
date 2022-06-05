#include "Array.h"
#include <iostream>
using namespace std;

template <class T>
class GrowableArray : public Array<T>{
	public:
		GrowableArray(int);
		T& operator[](int i);
};


template <typename T>
GrowableArray<T>::GrowableArray(int i):Array<T>(i){
	//생성자
}

template <typename T>
T& GrowableArray<T>::operator[](int i){
	static T tmp;
	if(i>=0 && i<this->len){
		return this->data[i];
	}
	else{
		T *newdata;
		int pre_len = this->len;
		this->len = i*2;
		newdata = new T[this->len];
		for(int j=0;j<pre_len;j++) newdata[j]=this->data[j];
		for(int k=pre_len;k<this->len;k++) newdata[k]=0;
		
		delete(this->data);
		this->data = new T[this->len];
		this->data = newdata;
		return this->data[i];
	}
}
