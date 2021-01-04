#include"matrix_exponentiation.h"

int** multiplyMatrix(int **matrix1, int **matrix2){
	int i;
	int **result = (int**)malloc(2 * sizeof(int*));
	for (i = 0; i < 2; i++)
		result[i] = (int*)malloc(2 * sizeof(int));
	result[0][0] = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]);
	result[0][1] = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]);
	result[1][0] = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]);
	result[1][1] = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]);
	return result;
}

int **fibMatrix(int **arr, int n){
	if (n == 1)
		return arr;
	if (n % 2 == 0)
		return multiplyMatrix(fibMatrix(arr, n / 2), fibMatrix(arr, n / 2));
	else
		return multiplyMatrix(multiplyMatrix(fibMatrix(arr, n / 2), fibMatrix(arr, n / 2)), fibMatrix(arr, 1));
}

void findFibLogN(int n){
	int i;
	int **initial = (int**)malloc(2 * sizeof(int*)), **fibMat;
	for (i = 0; i < 2; i++)
		initial[i] = (int*)malloc(2 * sizeof(int));
	initial[0][0] = 0;
	initial[0][1] = 1;
	initial[1][0] = 1;
	initial[1][1] = 1;
	fibMat = fibMatrix(initial, n);
	printf("Value: %ld\n", fibMat[1][1]);
}

void test_mat_exponentiation(){
	int n = 20;
	if (n <= 1)
		printf("%d\n", n);
	else
		findFibLogN(n - 1);
}
