#include"array_sum_recursion.h"

long sum_recursion(int* arr, int size)
{
	if (size == 0) return 0;
	if (size == 1) return arr[0];
	return sum_recursion(arr, size / 2) + sum_recursion(arr + size / 2, size - size / 2);
}

void test_sum_recursion()
{
	int size, iter;
	printf("\nEnter no of elements\t");
	scanf_s("%d", &size);
	int* arr = (int*)malloc(sizeof(int)*size);
	printf("Enter the array elements\n");
	for (iter = 0; iter < size; iter++)
	{
		scanf_s("%d", &arr[iter]);
	}
	printf("sum = %d\n", sum_recursion(arr, size));
}