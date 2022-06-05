#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct{
	int hours;
	int minutes;
	int seconds;
} Time;

int main(void){
	time_t timer;
	struct tm *t;

	timer=time(NULL);
	t=localtime(&timer);

	Time *curTime;
	curTime=(Time*)malloc(sizeof(Time));

	curTime->hours=t->tm_hour;
	curTime->minutes=t->tm_min;
	curTime->seconds=t->tm_sec;

	int num=1;
	int diff_h, diff_m, diff_s;
	char command[]="check";
	while(strcmp(command, "check")==0){
	printf("system > ");
	scanf("%s", command);

	if(strcmp(command, "check")!=0) break;

	printf("\n\tCheck Point #%02d\n", num++);

	timer=time(NULL);
	t=localtime(&timer);

	printf("\tCurrent Time = %02d : %02d : %02d\n", t->tm_hour, t->tm_min, t->tm_sec);
	printf("\tPrevious Time = %02d : %02d : %02d\n", curTime->hours, curTime->minutes, curTime->seconds);

	diff_h=(t->tm_hour)-(curTime->hours);
	diff_m=(t->tm_min)-(curTime->minutes);
	diff_s=(t->tm_sec)-(curTime->seconds);
	if(diff_s<0){
		diff_s+=60;
		diff_m-=1;
	}

	printf("\tElapsed Time = %02d : %02d : %02d\n", diff_h, diff_m, diff_s);

	curTime->hours=t->tm_hour;
	curTime->minutes=t->tm_min;
	curTime->seconds=t->tm_sec;

	}
	return 0;}
