#include "Str.h"
#include <iostream>
#include <string.h>
using namespace std;

Str::Str(int leng)
{
	//leng은 string의 길이
	len=leng;
	str=new char[len+1];
	str[len]='\0';
}

Str::Str(char *neyong)
{
	//neyong은 초기화할 내용이 들어감
	len=strlen(neyong);
	str=new char[len+1];
	strcpy(str, neyong);
	str[len]='\0';
}

Str::~Str()
{
	//소멸자
	delete(str);
}

int Str::length(void)
{
	//string의 길이를 리턴하는 함수
	return len;
}

char* Str::contents(void)
{
	//string의 내용을 리턴하는 함수
	return str;
}

int Str::compare(class Str& a)
{
	//a의 내용과 strcmp
	return strcmp(str, a.contents());

}

int Str::compare(char *a)
{
	//a의 내용과 strcmp
	return strcmp(str, a);
}

void Str::operator=(char *a)
{
	//string의 값을 대입
	delete(str);
	len=strlen(a);
	str=new char[len+1];
	strcpy(str, a);
	str[len]='\0';
}

void Str::operator=(class Str& a)
{
	//Str의 내용을 대입
	this->operator=(a.contents());
}
