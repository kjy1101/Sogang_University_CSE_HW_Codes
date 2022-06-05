#include "my_solver.h"
#include <cmath>

void program2_4()
{
	double lamda1 = 5, lamda2 = 10, lamda3 = 20;
	int i = 0, nr = 0;
	printf("������ ������ ����: ");
	scanf("%d", &nr);
	double U, X;
	double avg = 0, var = 0;
	double* X_data = (double*)malloc(sizeof(double) * nr);

	printf("1) lamda=%.2lf\n", lamda1);
	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		X_data[i] = Inversion(lamda1, U);
		//printf("%.15lf\n", X_data[i]);
		avg += X_data[i];
		i++;
	}
	avg /= nr;
	for (i = 0; i < nr; i++) {
		var = var + (X_data[i] - avg) * (X_data[i] - avg);
	}
	var /= nr;
	printf("���: %lf\n", avg);
	printf("�л�: %lf\n", var);
	printf("�̷л� ���: %lf\n", 1 / lamda1);
	printf("�̷л� �л�: %lf\n", 1 / (lamda1 * lamda1));
	printf("��� ������: %.2lf%%\n", abs((1 / lamda1) - avg) / (1 / lamda1) * 100);
	printf("�л� ������: %.2lf%%\n", abs((1 / (lamda1 * lamda1)) - var) / (1 / (lamda1 * lamda1)) * 100);


	printf("\n2) lamda=%.2lf\n", lamda2);
	i = 0;
	avg = 0;
	var = 0;
	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		X_data[i] = Inversion(lamda2, U);
		//printf("%.15lf\n", X_data[i]);
		avg += X_data[i];
		i++;
	}
	avg /= nr;
	for (i = 0; i < nr; i++) {
		var = var + (X_data[i] - avg) * (X_data[i] - avg);
	}
	var /= nr;
	printf("���: %lf\n", avg);
	printf("�л�: %lf\n", var);
	printf("�̷л� ���: %lf\n", 1 / lamda2);
	printf("�̷л� �л�: %lf\n", 1 / (lamda2 * lamda2));
	printf("��� ������: %.2lf%%\n", abs((1 / lamda2) - avg) / (1 / lamda2) * 100);
	printf("�л� ������: %.2lf%%\n", abs((1 / (lamda2 * lamda2)) - var) / (1 / (lamda2 * lamda2)) * 100);

	printf("\n3) lamda=%.2lf\n", lamda3);
	i = 0;
	avg = 0;
	var = 0;
	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		X_data[i] = Inversion(lamda3, U);
		//printf("%.15lf\n", X_data[i]);
		avg += X_data[i];
		i++;
	}
	avg /= nr;
	for (i = 0; i < nr; i++) {
		var = var + (X_data[i] - avg) * (X_data[i] - avg);
	}
	var /= nr;
	printf("���: %lf\n", avg);
	printf("�л�: %lf\n", var);
	printf("�̷л� ���: %lf\n", 1 / lamda3);
	printf("�̷л� �л�: %lf\n", 1 / (lamda3 * lamda3));
	printf("��� ������: %.2lf%%\n", abs((1 / lamda3) - avg) / (1 / lamda3) * 100);
	printf("�л� ������: %.2lf%%\n", abs((1 / (lamda3 * lamda3)) - var) / (1 / (lamda3 * lamda3)) * 100);

}

double Inversion(double lamda, double U) {
	return (-1 / lamda) * log(1 - U);
}