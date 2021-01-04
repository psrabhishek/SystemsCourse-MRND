#include"2_color_sort.h"

int main()
{
	int n;
	scanf_s("%d", &n);
	int *arr = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		scanf_s("%d", &arr[i]);
	int start = 0;
	int end = n - 1;
	while (start < end)
	{
		if (arr[start] == 1)
		{
			int temp = arr[start];
			arr[start] = arr[end];
			arr[end] = temp;
			start += 1;
			end -= 1;
		}
		else
			start += 1;
	}
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	getchar();
	getchar();
}