#include"3_color_sort.h"

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort_3_color(int arr[], int size)
{
	int lo = 0, mid = 0, hi =size - 1;

	while (mid <= hi)
	{
		if (arr[mid] == 0)
			swap(&arr[lo++], &arr[mid++]);
		else if (arr[mid] == 1)
			mid++;
			else if (arr[mid] == 2)
				swap(&arr[mid], &arr[hi--]);
	}
}

void test_3_color_sort()
{
	int size, iter;
	printf("Enter the no of elements in 3 color array\t");
	scanf_s("%d", &size);
	printf("Enter the array elements\n");
	int* arr = (int*)malloc(sizeof(int) * size);
	for (iter = 0; iter < size; iter++)
		scanf_s("%d", &arr[iter]);
	sort_3_color(arr, size);
	printf("The sorted order is\n");
	for (iter = 0; iter < size; iter++)
		printf("%d ", arr[iter]);
}
