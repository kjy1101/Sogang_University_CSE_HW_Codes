#include "my_solver.h"

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	int n;
	double h;
	
	fscanf(fp_r, "%d %lf", &n, &h);
	

	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;

	while (EOF!= fscanf(fp_r, "%lf %lf", &x[i], &y[i])) {
		i++;
	}

	/* x 정규화 (0~1) */
	double* nx = (double*)malloc(sizeof(double) * n);
	double xmin = x[0];
	double xmax = x[n - 1];

	for (i = 0; i < n; i++) {
		nx[i] = (x[i] - xmin) / (xmax - xmin);
	}
	double nh = nx[1] - nx[0];


	/* y 정규화 : f(x)->p(x) = f(x)/(x0부터 xn까지 f(x)적분) */
	double* px = (double*)malloc(sizeof(double) * n);
	double integral_fx = 0;
	double mid_term = 0;

	integral_fx = y[0] + y[n];
	mid_term = 0;
	for (int j = 1; j < n - 1; j++) {
		mid_term += y[j];
	}
	integral_fx += (2 * mid_term);
	integral_fx = integral_fx * nh / 2;

	for (i = 0; i < n; i++) {
		px[i] = y[i] / integral_fx;
	}


	
	fprintf(fp_w, "%d %lf\n", n, nh);
	for (i = 0; i < n; i++) {
		fprintf(fp_w, "%lf %lf\n", nx[i], px[i]);
	}



	int x_point0, x_point25, x_point5, x_point75, x_point1;
	x_point0 = 0;
	x_point1 = n - 1;
	int flag = 0;
	for (i = 1; i < n - 1; i++) {
		if (flag == 0) {
			if (nx[i] > 0.25) {
				x_point25 = i - 1;
				flag = 1;
			}
		}
		else if (flag == 1) {
			if (nx[i] > 0.5) {
				x_point5 = i - 1;
				flag = 2;
			}
		}
		else if (flag == 2) {
			if (nx[i] > 0.75) {
				x_point75 = i - 1;
				break;
			}
		}
	}

	/*printf("%lf\n", nx[x_point25]);
	printf("%lf\n", nx[x_point5]);
	printf("%lf\n", nx[x_point75]);*/

	integral_fx = px[x_point0] + px[x_point1];
	mid_term = 0;
	for (int j = x_point0 + 1; j < x_point1 - 1; j++) {
		mid_term += px[j];
	}
	integral_fx += (2 * mid_term);
	double result1 = integral_fx * nh / 2;
	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", result1);



	integral_fx = px[x_point0] + px[x_point25];
	mid_term = 0;
	for (int j = x_point0 + 1; j < x_point25 - 1; j++) {
		mid_term += px[j];
	}
	integral_fx += (2 * mid_term);
	double result2 = integral_fx * nh / 2;
	if (nx[x_point25] < 0.25) {
		double remain2 = (px[x_point25] + ((px[x_point25 + 1] - px[x_point25]) / (nx[x_point25 + 1] - nx[x_point25])) * ((0.25 - nx[x_point25]) / 2)) * (0.25 - nx[x_point25]);
		result2 += remain2;
	}
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", result2);



	integral_fx = px[x_point25] + px[x_point5];
	mid_term = 0;
	for (int j = x_point25 + 1; j < x_point5 - 1; j++) {
		mid_term += px[j];
	}
	integral_fx += (2 * mid_term);
	double result3 = integral_fx * nh / 2;
	if (nx[x_point5] < 0.5) {
		double remain3 = (px[x_point5] + ((px[x_point5 + 1] - px[x_point5]) / (nx[x_point5 + 1] - nx[x_point5])) * ((0.5 - nx[x_point5]) / 2)) * (0.5 - nx[x_point5]);
		result3 += remain3;
	}
	if (nx[x_point25] < 0.25) {
		double remain3 = (px[x_point25] + ((px[x_point25 + 1] - px[x_point25]) / (nx[x_point25 + 1] - nx[x_point25])) * ((0.25 - nx[x_point25]) / 2)) * (0.25 - nx[x_point25]);
		result3 -= remain3;
	}
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", result3);



	integral_fx = px[x_point5] + px[x_point75];
	mid_term = 0;
	for (int j = x_point5 + 1; j < x_point75 - 1; j++) {
		mid_term += px[j];
	}
	integral_fx += (2 * mid_term);
	double result4 = integral_fx * nh / 2;
	if (nx[x_point75] < 0.75) {
		double remain4 = (px[x_point75] + ((px[x_point75 + 1] - px[x_point75]) / (nx[x_point75 + 1] - nx[x_point75])) * ((0.75 - nx[x_point75]) / 2)) * (0.75 - nx[x_point75]);
		result4 += remain4;
	}
	if (nx[x_point5] < 0.5) {
		double remain4 = (px[x_point5] + ((px[x_point5 + 1] - px[x_point5]) / (nx[x_point5 + 1] - nx[x_point5])) * ((0.5 - nx[x_point5]) / 2)) * (0.5 - nx[x_point5]);
		result4 -= remain4;
	}
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", result4);
	


	integral_fx = px[x_point75] + px[x_point1];
	mid_term = 0;
	for (int j = x_point75 + 1; j < x_point1 - 1; j++) {
		mid_term += px[j];
	}
	integral_fx += (2 * mid_term);
	double result5 = integral_fx * nh / 2;
	if (nx[x_point75] < 0.75) {
		double remain5 = (px[x_point75] + ((px[x_point75 + 1] - px[x_point75]) / (nx[x_point75 + 1] - nx[x_point75])) * ((0.75 - nx[x_point75]) / 2)) * (0.75 - nx[x_point75]);
		result5 -= remain5;
	}
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", result5);


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
