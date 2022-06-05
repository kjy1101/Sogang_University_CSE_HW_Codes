#include <stdio.h>
#include <math.h>

typedef struct{
	double x; //구의 x좌표
	double y; //구의 y좌표
	double z; //구의 z좌표
	double r; //구의 반지름
} SPHERE;

double Distance(SPHERE, SPHERE); //두 구의 중심 사이의 거리
double CrossSectionArea(SPHERE, SPHERE); //두 구의 단면적의 합
double SurfaceArea(SPHERE, SPHERE); //두 구의 겉넓이의 합
double Volume(SPHERE, SPHERE); //두 구의 부피의 합

int main(void){
	SPHERE sphere1, sphere2;
	printf("Type First Sphere Coordinate : ");
	scanf("%lf %lf %lf", &(sphere1.x), &(sphere1.y), &(sphere1.z));
	printf("Type First Sphere Radius : ");
	scanf("%lf", &(sphere1.r));

	printf("Type Second Sphere Coordinate : ");
	scanf("%lf %lf %lf", &(sphere2.x), &(sphere2.y), &(sphere2.z));
	printf("Type Second Sphere Radius : ");
	scanf("%lf", &(sphere2.r));

	//두 구가 떨어져있을 때 => 두 구의 단면적의 넓이의 합
	//두 구가 접할 때 => 두 구의 겉넓이의 합
	//두 구가 겹칠 때 => 두 구의 부피의 합
	
	//두 점 사이의 거리 > 반지름1+반지름2 : 떨어져 있음
	//두 점 사이의 거리 = 반지름1+반지름2 : 접함
	//두 점 사이의 거리 < 반지름1+반지름2 : 겹침

	double distance, sum_r;
	distance=Distance(sphere1, sphere2);
	sum_r=sphere1.r+sphere2.r;

	if(distance > sum_r){
		//떨어져 있을 때
		printf("Sum of Cross Section Area : %.2lf\n", CrossSectionArea(sphere1, sphere2));
	}
	else if(distance==sum_r){
		//접할 때
		printf("Sum of Surface Area : %.2lf\n", SurfaceArea(sphere1, sphere2));
	}
	else{
		//겹칠 때
		printf("Sum of Volume : %.2lf\n", Volume(sphere1, sphere2));
	}
	return 0;}

double Distance(SPHERE s1, SPHERE s2){
	double d;
	d=pow(s1.x-s2.x,2)+pow(s1.y-s2.y,2)+pow(s1.z-s2.z,2);
	return sqrt(d);
}
double CrossSectionArea(SPHERE s1, SPHERE s2){
	double a;
	a=pow(s1.r,2)+pow(s2.r,2);
	return a*3.14;
}
double SurfaceArea(SPHERE s1, SPHERE s2){
	double sa;
	sa=pow(s1.r,2)+pow(s2.r,2);
	return sa*4*3.14;
}
double Volume(SPHERE s1, SPHERE s2){
	double v;
	v=pow(s1.r,3)+pow(s2.r,3);
	return v*4*3.14/3;
}
