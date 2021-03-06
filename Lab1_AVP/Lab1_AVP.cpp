#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <immintrin.h>

#define four 16
#define eight 16
#define size 200


__forceinline double count_out(double** matrix_0, double** matrix_1, int i, int j) {
	double out = 0;
	double* mat1;
	double mat2;
	for (int l = 0; l < eight; l++)
	{
		mat1 = matrix_1[l];
		mat2 = matrix_0[i][l];

		for (int k = j; k <= j; k++)
		{
			out += mat1[k] * mat2;
		}
	}
	return out;
}


double count_out_FMA(double** matrix_0, double** matrix_1, int i, int j) {
	double out = 0;
	double d_null[4] = { 0 };
	double _out[8] = { 0 };

	__m256d temp_0;
	__m256d temp_1;
	__m256d temp_2;
	__m256d temp_null = _mm256_load_pd(d_null);

	for (int k = 0; k < eight; k+=4)
	{
		double tmp[4] = { 0 };
		for (int l = 0; l < 4; l++)
		{
			tmp[l] = matrix_1[k + l][j];
		}
		temp_0 = _mm256_load_pd(matrix_0[i] + k);
		temp_1 = _mm256_load_pd(tmp);
		temp_2 = _mm256_fmadd_pd(temp_0, temp_1, temp_null);
		_mm256_store_pd(_out + k, temp_2);
	}
	
	for (int k = 0; k < 4; k++)
	{
		out += _out[k] + _out[k+4];
	}
	return out;
}


int main()
{
	srand(static_cast <unsigned> (time(0)));

	double**** matrix_in_0 = new double ***[size];
	double**** matrix_in_1 = new double ***[size];
	double**** matrix_out_0 = new double ***[size];
	double**** matrix_out_1 = new double ***[size];
	double**** matrix_out_2 = new double ***[size];

	for (int i = 0; i < size; i++) {
		matrix_in_0[i] = new double **[size];
		matrix_in_1[i] = new double **[size];
		matrix_out_0[i] = new double **[size];
		matrix_out_1[i] = new double **[size];
		matrix_out_2[i] = new double **[size];

		for (int j = 0; j < size; j++) {
			matrix_in_0[i][j] = new double*[four];
			matrix_in_1[i][j] = new double*[eight];
			matrix_out_0[i][j] = new double*[four];
			matrix_out_1[i][j] = new double*[four];
			matrix_out_2[i][j] = new double*[four];

			for (int k = 0; k < four; k++) {
				matrix_in_0[i][j][k] = new double[eight];
				matrix_out_0[i][j][k] = new double[four];
				matrix_out_1[i][j][k] = new double[four];
				matrix_out_2[i][j][k] = new double[four];

				for (int l = 0; l < eight; l++) {
					matrix_in_0[i][j][k][l] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 100));
				}

				for (int l = 0; l < four; l++) {
					matrix_out_0[i][j][k][l] = 0.0f;
					matrix_out_1[i][j][k][l] = 0.0f;
					matrix_out_2[i][j][k][l] = 0.0f;
				}
			}

			for (int k = 0; k < eight; k++) {
				matrix_in_1[i][j][k] = new double[four];

				for (int l = 0; l < four; l++) {
					matrix_in_1[i][j][k][l] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 100));
				}
			}
		}
	}

	double mat1;
	double* mat2;

	clock_t tStart = clock();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int l = 0; l < size; l++)
			{
				for (int k = 0; k < four; k++)
				{
					for (int m = 0; m < eight; m++)
					{
						mat1 = matrix_in_0[i][j][k][m];
						mat2 = matrix_in_1[i][j][m];
						for (int e = 0; e < four; e++)
						{
							matrix_out_0[i][j][k][e] += mat1 * mat2[e];
						}
					}
				}
			}
		}
	}

	printf("Time taken vector: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);




	clock_t tStart_nv = clock();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int l = 0; l < size; l++)
			{
				for (int k = 0; k < four; k++)
				{
#pragma loop(no_vector)
					for (int e = 0; e < four; e++)
					{
						//count_out(matrix_in_0[l][j], matrix_in_1[i][l], matrix_out_1[i][j], k, e);
						matrix_out_1[i][j][k][e] += count_out(matrix_in_0[l][j], matrix_in_1[i][l], k, e);
					}
				}
			}
		}
	}




	printf("Time taken no_vector: %.2fs\n", (double)(clock() - tStart_nv) / CLOCKS_PER_SEC);

#pragma region FMA
	clock_t tStart_fma = clock();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int l = 0; l < size; l++)
			{
				for (int k = 0; k < four; k++)
				{
					for (int e = 0; e < four; e += 4)
					{
						matrix_out_2[i][j][k][e] += count_out_FMA(matrix_in_0[l][j], matrix_in_1[i][l], k, e);
					}
				}
			}
		}
	}

	printf("Time taken FMA: %.2fs\n", (double)(clock() - tStart_fma) / CLOCKS_PER_SEC);
#pragma endregion


	system("pause");
	return 0;
}