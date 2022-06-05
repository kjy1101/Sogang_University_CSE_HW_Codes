#include "my_solver.h"

extern "C"
{
	int rpoly_(double*, int*, double*, double*, long int*);
}

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;
	double fx[2];
	double temp[2];

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/
		i = 0;
		while (EOF != fscanf(fp_r, "%lf", &poly[i])) {
			i++;
		}

		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);
		if (fail) {
			printf("fail\n\n");
			fprintf(fp_w, "fail\n");
			continue;
		}
		for (i = 0; i < DEGREE; i++) {
			printf("%10f ", zeror[i]);
			fprintf(fp_w, "%10f ", zeror[i]);
		}
		printf("\n");
		fprintf(fp_w, "\n");
		for (i = 0; i < DEGREE; i++) {
			printf("%10f ", zeroi[i]);
			fprintf(fp_w, "%10f ", zeroi[i]);
		}
		printf("\n");
		fprintf(fp_w, "\n");

		
		for (i = 0; i < DEGREE; i++) {
			temp[0] = zeror[i];
			temp[1] = zeroi[i];
			fx[0] = 0;
			fx[1] = 0;
			int poly_index = 0;
			for (int k = 1; k <= DEGREE; k++) {
				temp[0] = zeror[i];
				temp[1] = zeroi[i];
				for (int j = DEGREE - k; j > 0; j--) { //x^k
					double temp0 = temp[0];
					temp[0] = temp0 * zeror[i] - temp[1] * zeroi[i];
					temp[1] = temp0 * zeroi[i] + temp[1] * zeror[i];
				}
				fx[0] += temp[0] * poly[poly_index];
				fx[1] += temp[1] * poly[poly_index];
				poly_index++;
			}
			fx[0] += poly[DEGREE];
			printf("|f(x*)| = %10f + %10fi\n", fx[0], fx[1]);
			fprintf(fp_w, "|f(x*)| = %10f + %10fi\n", fx[0], fx[1]);
		}
		printf("\n");
		fprintf(fp_w, "\n");

		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}