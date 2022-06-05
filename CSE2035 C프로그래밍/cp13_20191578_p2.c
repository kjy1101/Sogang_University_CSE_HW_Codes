#include <stdio.h>
struct CoinBox{
	int n500;
	int n100;
	int n50;
	int n10;
};

int main(void){
	int price;
	scanf("%d", &price);

	struct CoinBox coin;
	coin.n500=price/500;
	price%=500;
	coin.n100=price/100;
	price%=100;
	coin.n50=price/50;
	price%=50;
	coin.n10=price/10;

	printf("%d\n%d\n%d\n%d\n", coin.n500, coin.n100, coin.n50, coin.n10);
	
	return 0;}
