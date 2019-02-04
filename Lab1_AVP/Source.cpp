//#include <Windows.h>
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <time.h>
//
//float count_out(float** matrix_0, float** matrix_1, int i, int j) {
//	float out = 0;
//	for (int k = 0; k < 8; k++)
//	{
//		out += matrix_0[i][k] * matrix_1[k][j];
//	}
//	return out;
//}
//
//
//int main()
//{
//	srand(static_cast <unsigned> (time(0)));
//
//	float**** matrix_in_0 = new float ***[500];
//	float**** matrix_in_1 = new float ***[500];
//	float**** matrix_out_0 = new float ***[500];
//	float**** matrix_out_1 = new float ***[500];
//
//	for (int i = 0; i < 500; i++) {
//		matrix_in_0[i] = new float **[500];
//		matrix_in_1[i] = new float **[500];
//		matrix_out_0[i] = new float **[500];
//		matrix_out_1[i] = new float **[500];
//
//		for (int j = 0; j < 500; j++) {
//			matrix_in_0[i][j] = new float*[4];
//			matrix_in_1[i][j] = new float*[8];
//			matrix_out_0[i][j] = new float*[4];
//			matrix_out_1[i][j] = new float*[4];
//
//			for (int k = 0; k < 4; k++) {
//				matrix_in_0[i][j][k] = new float[8];
//				matrix_out_0[i][j][k] = new float[4];
//				matrix_out_1[i][j][k] = new float[4];
//
//				for (int l = 0; l < 8; l++) {
//					matrix_in_0[i][j][k][l] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
//				}
//
//				for (int l = 0; l < 4; l++) {
//					matrix_out_0[i][j][k][l] = 0.0f;
//					matrix_out_1[i][j][k][l] = 0.0f;
//				}
//			}
//
//			for (int k = 0; k < 8; k++) {
//				matrix_in_1[i][j][k] = new float[4];
//
//				for (int l = 0; l < 4; l++) {
//					matrix_in_1[i][j][k][l] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
//				}
//			}
//		}
//	}
//
//	clock_t tStart = clock();
//
//	for (int i = 0; i < 500; i++) {
//		for (int j = 0; j < 500; j++) {
//			for (int l = 0; l < 500; l++) {
//				for (int k = 0; k < 4; k++) {
//					for (int e = 0; e < 4; e++) {
//						matrix_out_0[i][j][k][e] += count_out(matrix_in_0[i][j], matrix_in_1[i][j], k, e);
//					}
//				}
//				//matrix_out_0[i][j] += matrix_in_0[i][l] * matrix_in_1[l][j];
//			}
//		}
//	}
//
//	printf("Time taken vector: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
//
//	clock_t tStart_nv = clock();
//
//#pragma loop(no_vector)
//	for (int i = 0; i < 500; i++)
//	{
//		for (int j = 0; j < 500; j++)
//		{
//			for (int k = 0; k < 4; k++)
//			{
//				for (int e = 0; e < 4; e++)
//				{
//					matrix_out_1[i][j][k][e] += count_out(matrix_in_0[i][j], matrix_in_1[i][j], k, e);
//				}
//			}
//		}
//	}
//	printf("Time taken no_vector: %.2fs\n", (double)(clock() - tStart_nv) / CLOCKS_PER_SEC);
//
//#pragma loop(vector)
//	for (int i = 0; i < 500; i++)
//	{
//		for (int j = 0; j < 500; j++)
//		{
//			for (int k = 0; k < 4; k++)
//			{
//				for (int e = 0; e < 4; e++)
//				{
//					if (matrix_out_0[i][j][k][e] != matrix_out_1[i][j][k][e])
//					{
//						std::cout << "\n\nError\n\n";
//					}
//				}
//			}
//		}
//	}
//
//	std::cout << "\n" << matrix_out_0[22][22][2][2] << "\n";
//	std::cout << "\n" << matrix_out_1[22][22][2][2] << "\n";
//
//	system("pause");
//	return 0;
//}