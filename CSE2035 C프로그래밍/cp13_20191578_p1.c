#include <stdio.h>
enum Date{
	sun, mon, tue, wed, thu, fri, sat
};

struct Calendar{
	int year, month, day;
	enum Date date;
	char *dateString;
};

enum Date getDate(int y, int m, int d);
char *getDay(enum Date currDate);

int main(void){
	int y,m,d;
	scanf("%d %d %d", &y, &m, &d);
	struct Calendar C={y,m,d};
	C.date=getDate(y,m,d);
	C.dateString=getDay(C.date);

	printf("%s\n", C.dateString);

	return 0;}

enum Date getDate(int y, int m, int d){
	return (y+y/4-y/100+y/400+(13*m+8)/5+d)%7;}

char *getDay(enum Date currDate){
	switch(currDate){
		case sun:
			return "Sunday";
		case mon:
			return "Monday";
		case tue:
			return "Tuesday";
		case wed:
			return "Wednesday";
		case thu:
			return "Thursday";
		case fri:
			return "Friday";
		case sat:
			return "Saturday";
	}
}
