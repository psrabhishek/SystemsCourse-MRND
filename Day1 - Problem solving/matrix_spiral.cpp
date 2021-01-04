#include"matrix_spiral.h"


int* spiral(int** matrix, int r, int c)
{
	int * sp = (int*)malloc(sizeof(int)*(r * c)), i = 0, j = 0, ind = 0, k = 0, l = 0;
	while (k<r && l < c)
	{
		while (j < c)
		{
			sp[ind++] = matrix[i][j++];

		}
		k++;
		i++;
		j--;
		while (i < r)
		{
			sp[ind++] = matrix[i++][j];

		}
		c--;
		j--;
		i--;
		while (j >= l)
		{
			sp[ind++] = matrix[i][j--];

		}
		r--;
		i--;
		j++;
		while (i >= k)
		{
			sp[ind++] = matrix[i--][j];

		}
		l++;
		j++;
		i++;
	}
	return sp;
}

int* spiral_recursion(int **a, int lr, int rr, int lc, int rc)
{

	if (lr>rr || lc>rc)
		return;
	int  r = 0, q = 0;
	for (int i = lc; i <= rc; i++)
	{
		printf("%d  ", a[lr][i]);
	}
	for (int i = lr + 1; i <= rr; i++){
		r = 1;
		printf("%d  ", a[i][rc]);
	}
	if (r == 1)
		for (int i = rc - 1; i >= lc; i--){
			q = 1;
			printf("%d  ", a[rr][i]);
		}
	if (q == 1)
		for (int i = rr - 1; i>lr; i--)
			printf("%d  ", a[i][lc]);
	return spiral_recursion(a, lr + 1, rr - 1, lc + 1, rc - 1);

}

void test_matrix_spiral()
{
	int m, n;
	printf("Enter no. of rows and columns respectively\n");
	scanf_s("%d%d", &m, &n);
	int **a = (int**)malloc(m*sizeof(int*));
	for (int i = 0; i < m; i++)
		a[i] = (int*)malloc(n*sizeof(int));
	printf("enter i/p array\n");
	for (int i = 0; i < m; i++)
		for (int j = 0; j< n; j++)
			scanf_s("%d", &a[i][j]);

	spiral_recursion(a, 0, m - 1, 0, n - 1);

	printf("\nEnter any to exit...");
	int temp;
	scanf_s("%d", &temp);
}