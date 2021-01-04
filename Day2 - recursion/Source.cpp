#include"MergeSort_dll.h"
#include"array_sum_recursion.h"
#include<set>

using namespace std;

int stair_case(int n, int k)
{
	if (n < 2) return 1;

	int res = 0, iter;
	if (n < k) k = n;
	for (iter = 1; iter <= k; iter++)
		res += stair_case(n - iter, k);
	return res;
}

void print_upto_n_digits(int n, int prev)
{
	if (n <= 1)
	{
		printf("%d\n", prev);
		return;
	}
	for (int iter = 0; iter < 10; iter++)
		print_upto_n_digits(n - 1, prev * 10 + iter);
}

void print_num_mirror(int n)
{
	if (n < 1) return;
	print_num_mirror(n / 10);
	char c[] = { '0', '1', '2', 'E', 'h', '5', '9', 'L', '8', '6' };
	printf("%c", c[n%10]);
}

void permutate_array(int* arr, char* str, int level, int size, set<int> hash)
{
	if (level == size)
	{
		str[level] = '\0';
		printf("%s\n", str);
		return;
	}

	for (int iter = 0; iter < size; iter++)
	{
		if (hash.find(iter) != hash.end())
			continue;
		hash.insert(iter);
		str[level] = '0' + arr[iter];
		permutate_array(arr, str, level + 1, size, hash);
		hash.erase(iter);
	}
}

void permutate_array_no_repetition(int* arr, char* str, int level, int size, set<int> hash, char* prev)
{
	if (level == size)
	{
		str[level] = '\0';
		if (strcmp(str, prev));
			printf("%s\n", str);
		prev = str;
		return;
	}

	for (int iter = 0; iter < size; iter++)
	{
		if (hash.find(iter) != hash.end())
			continue;
		hash.insert(iter);
		str[level] = '0' + arr[iter];
		permutate_array_no_repetition(arr, str, level + 1, size, hash, prev);
		hash.erase(iter);
	}
}

int get_match_in_dir(char** grid, char* str, int len, int r, int c, int R, int C, int ind, int x, int y)
{
	if (r < 0 || c < 0 || r >= R || c >= C)
		return 0;
	if (str[ind] != grid[r][c])
		return 0;
	if (!str[ind+1])
		return 1;
	return get_match_in_dir(grid, str, len, r +x, c + y, R, C, ind + 1, x, y);

}

int str_matrix_match(char**grid, char* str, int len, int r, int c, int R, int C)
{
	int x[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
	int y[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
	int count = 0;

	for (int dir = 0; dir < 8; dir++)
	{
		if (get_match_in_dir(grid, str, len, r +x[dir], c + y[dir], R, C, 1, x[dir], y[dir]))
		{
			printf("(%d,%d) => (%d, %d)\n", r, c, r + x[dir]*(len-1), c + y[dir]*(len-1));
			count++;
		}
		/* same code in iterative fashion
		---------------------------------------
		int row_iter = r + x[dir], col_iter = c + y[dir], ind = 1;
		while (row_iter >= 0 && col_iter >= 0 && row_iter < R && col_iter < C)
		{
			if (str[ind++] != grid[row_iter][col_iter])
			{ 
				ind--;
				break;
			}
			row_iter += x[dir];
			col_iter += y[dir];
		}
		if (!str[ind])
		{
			printf("(%d,%d) => (%d, %d)\n", r, c, row_iter - x[dir], col_iter - y[dir]);
			count++;
		}*/
	}
	return count;
}

int main()
{
	test_merge_sort_dll();
	//test_sum_recursion();
	/*int a[] = { 1, 1, 3, 5 };
	set<int> hash;
	char str[5] = "";
	permutate_array_no_repetition(a, str, 0, 4, hash, "");*/
	int n;
	scanf_s("%d", &n);
	print_upto_n_digits(n, 0);

	char* s[3];
	s[0] = "tit";
	s[1] = "iii";
	s[2] = "tit";
	char* str = "tit";
	int i, j, count = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			if (s[i][j] == str[0])
				count += str_matrix_match(s, str, 3, i, j, 3, 3);
	}
	printf("\ncount = %d\n", count);
	getchar();
	getchar();
	return 0;
}