#include"matrix_transpose.h"

int** transpose(int** matrix, int r, int c)
{
	int ** new_mat = (int**)malloc(sizeof(int*)*c);
	int i, j;
	for (i = 0; i < c; i++)
		new_mat[i] = (int*)malloc(sizeof(int)*r);
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			new_mat[j][i] = matrix[i][j];
	return new_mat;
}

void test_matrix_transpose()
{

}