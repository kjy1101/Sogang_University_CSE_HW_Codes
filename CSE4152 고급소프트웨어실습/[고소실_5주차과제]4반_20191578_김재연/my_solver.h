#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <Windows.h>

#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);

#define DELTA 0.000000000001
#define Nmax 100
#define EPSILON 0.00000000001
#define MY_RAND_MAX 32767

void program2_1();
void program2_2();

// HOMEWORK
void program2_2_a(void);
void program2_2_b(void);
void program2_2_c(void);
void program2_3(void);
void program2_4(void);
double Inversion(double lamda, double U);
double Bisection(double aa, double bb, double U, double* y, double h, double* x, int n);
double newfunction(double xx, double U, double* y, double h, double* x, int n);
double Secant(double aa, double bb, double U, double* y, double h, double* x, int n);
double Newton(double aa, double U, double* y, double h, double* x, int n);

#endif  // __MY_SOLVER_H__
