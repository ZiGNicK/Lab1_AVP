#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <immintrin.h>

#define four 4
#define eight 8
#define size 50
void func1() {};

float count_out(float** matrix_0, float** matrix_1, int i, int j) {
	float* m0 = matrix_0[i];
	//float* m1 = matrix_1[j];
	float out = 0;
	for (int k = 0; k < eight; k++)
	{
		out += m0[k] * matrix_1[k][j];
	}
	func1();
	return out;
}

//float count_out_FMA(float** matrix_0, float** matrix_1, int i, int j) {
//	float out = 0;
//	for (int k = 0; k < eight; k++)
//	{
//		out += _mm_fmadd_ss((matrix_0[i][k], )  * matrix_1[k][j];
//	}
//	return out;
//}


int main()
{
	srand(static_cast <unsigned> (time(0)));

	float**** matrix_in_0 = new float ***[size];
	float**** matrix_in_1 = new float ***[size];
	float**** matrix_out_0 = new float ***[size];
	float**** matrix_out_1 = new float ***[size];

	for (int i = 0; i < size; i++) {
		matrix_in_0[i] = new float **[size];
		matrix_in_1[i] = new float **[size];
		matrix_out_0[i] = new float **[size];
		matrix_out_1[i] = new float **[size];

		for (int j = 0; j < size; j++) {
			matrix_in_0[i][j] = new float*[four];
			matrix_in_1[i][j] = new float*[eight];
			matrix_out_0[i][j] = new float*[four];
			matrix_out_1[i][j] = new float*[four];

			for (int k = 0; k < four; k++) {
				matrix_in_0[i][j][k] = new float[eight];
				matrix_out_0[i][j][k] = new float[four];
				matrix_out_1[i][j][k] = new float[four];

				for (int l = 0; l < eight; l++) {
					matrix_in_0[i][j][k][l] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
				}

				for (int l = 0; l < four; l++) {
					matrix_out_0[i][j][k][l] = 0.0f;
					matrix_out_1[i][j][k][l] = 0.0f;
				}
			}

			for (int k = 0; k < eight; k++) {
				matrix_in_1[i][j][k] = new float[four];

				for (int l = 0; l < four; l++) {
					matrix_in_1[i][j][k][l] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
				}
			}
		}
	}

	clock_t tStart = clock();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int l = 0; l < size; l++)
			{
				for (int m = 0; m < size; m++)
				{
					for (int k = 0; k < four; k++)
					{
						for (int e = 0; e < four; e++)
						{
							matrix_out_0[i][j][k][e] += count_out(matrix_in_0[l][j], matrix_in_1[i][m], k, e);
						}
					}
				}
			}
		}
	}

	printf("Time taken vector: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	clock_t tStart_nv = clock();

#pragma loop(no_vector)
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int l = 0; l < size; l++)
			{
				for (int m = 0; m < size; m++)
				{
					for (int k = 0; k < four; k++)
					{
						for (int e = 0; e < four; e++)
						{
							matrix_out_1[i][j][k][e] += count_out(matrix_in_0[l][j], matrix_in_1[i][m], k, e);
						}
					}
				}
			}
		}
	}
	printf("Time taken no_vector: %.2fs\n", (double)(clock() - tStart_nv) / CLOCKS_PER_SEC);

//#pragma region FMA
//	clock_t tStart = clock();
//
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			for (int l = 0; l < size; l++)
//			{
//				for (int m = 0; m < size; m++)
//				{
//					for (int k = 0; k < four; k++)
//					{
//						for (int e = 0; e < four; e++)
//						{
//							matrix_out_0[i][j][k][e] += count_out_FMA(matrix_in_0[l][j], matrix_in_1[i][m], k, e);
//						}
//					}
//				}
//			}
//		}
//	}
//
//	printf("Time taken FMA: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
//#pragma endregion

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < four; k++)
			{
				for (int e = 0; e < four; e++)
				{
					if (matrix_out_0[i][j][k][e] != matrix_out_1[i][j][k][e])
					{
						std::cout << "\n\nError\n\n";
					}
				}
			}
		}
	}

	std::cout << "\n" << matrix_out_0[22][22][2][2] << "\n";
	std::cout << "\n" << matrix_out_1[22][22][2][2] << "\n";

	system("pause");
	return 0;
}