#ifndef __ARRAY__
#define __ARRAY__
#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class Array{
	protected:
		T *data;
		int len;
	public:
			Array(int size);
			~Array();

			int length() const;

			virtual T& operator[](int i); //원소삽입
			T operator[](int i)const; //원소반환

			void print();
};



template <typename T>
Array<T>::Array(int size){
	//생성자
	if(size<=0){
		cout << "Size is less than 0.\n";
		exit(1);
	}
	else{
		data = new T[size];
		len=0;
		for(int i=0;i<size;i++) len++;
	}
}



template <typename T>
Array<T>::~Array(){
	//소멸자
	delete(data);
}



template <typename T>
int Array<T>::length() const{
	//길이반환
	return len;
}



template <typename T>
T& Array<T>::operator[](int i){
	//원소삽입
	static T tmp;
	if(i>=0 && i<len){
		return data[i];
	}
	else{
		cout << "Array bound error!\n";
		return tmp;
	}
}



template <typename T>
T Array<T>::operator[](int i) const{
	//원소반환
	if(i>=0 && i<len){
		return data[i];
	}
	else{
		cout << "Array bound error!\n";
		return 0;
	}
}



template <typename T>
void Array<T>::print(){
	//출력
	int i;
	cout << "[";
	for(i=0;i<len;i++){
		cout << " " << data[i];
	}
	cout << "]";
	cout << endl;
}

#endif
