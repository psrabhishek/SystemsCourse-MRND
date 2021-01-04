/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX 10000000
#define MIL 1000000
#define FILES (MAX/1000000) + 1


int main()
{
	int i, j, k, num, fileno;
	char* occur;
	FILE* fp[FILES], *res, *ip;
	char** files = (char**) calloc(FILES, sizeof(char*));


	for (i = 0; i < FILES; i++)
	{
		files[i] = (char*)calloc(15, sizeof(char));
		_itoa(i, files[i], 10);
		strcat(files[i], ".txt");
	}

	ip= fopen("main.txt", "r+");
	res = fopen("res.txt", "w");

	for (i = 0; i < FILES; i++)
	{
		fp[i] = fopen(files[i], "w+");
	}
	while (!feof(ip))
	{
		fscanf(ip, "%d", &num);
		fileno = (num / MIL);
		fprintf(fp[fileno], "%d\n", num);
	}

	for (i = 0; i <FILES; i++)
	{
		fseek(fp[i], 0, SEEK_SET);
		occur = (char*)calloc(125000, sizeof(char));
		while (!feof(fp[i]))
		{
			fscanf(fp[i], "%d", &num);
			if (!num && i ) continue;
			num %= MIL;
			occur[num / 8] = occur[num / 8] | 1 << (num % 8);
		}
		fseek(fp[i], 0, SEEK_SET);
		for (j = 0; j < 125000; j++)
		{
			for (k = 0; k < 8; k++)
				if (occur[j] & 1<<k)
					fprintf(res, "%d\n", j*8+ k + (i)*MIL);
		}
		free(occur);
	}

	return 0;
}*/