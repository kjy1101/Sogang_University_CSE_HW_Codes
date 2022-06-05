#include "GrowableArray.h"
#include <iostream>
using namespace std;

int main(void){
	//GrowableArray test (int)
	cout << "GrowableArray<int> Test" << endl;
	GrowableArray<int> g(10);
	int i;
	for(i=0;i<g.length();i++) g[i]=2*i+3;
	cout << "g(10)"; g.print();
	g[13]=13;
	cout << "g(26)"; g.print();

	//GrowableArray test (double)
	cout << "GrowableArray<double> Test" << endl;
	GrowableArray<double> dg(10);
	int j;
	for(j=0;j<dg.length();j++) dg[j]=2*j+3.14;
	cout << "dg(10)"; dg.print();
	dg[13]=13.31;
	cout << "dg(26)"; dg.print();
	return 0;
}
