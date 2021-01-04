/*
Uses o(1) space and no additional files are created
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX 10000000
#define MIL 1000000
#define WORD 32
#define BYTES MIL/WORD
#define FILES (MAX/1000000) + 1


int main() {
	int i, j, k, num, fileno;
	long* occur;
	FILE  *res, *ip;


	ip = fopen("main.txt", "r+");
	res = fopen("res.txt", "w");

	

	for (i = 0; i < FILES; i++)
	{
		occur = (long*)calloc(BYTES, sizeof(long));
		fseek(ip, 0, SEEK_SET);
		while (!feof(ip))
		{
			fscanf(ip, "%d", &num);
			if (num / MIL == i)
			{
				num %= MIL;
				occur[num / WORD] = occur[num / WORD] | 1 << (num % WORD);
			}
		}
		for (j = 0; j < BYTES; j++)
		{
			for (k = 0; k < WORD; k++)
				if (occur[j] & 1 << k)
					fprintf(res, "%d\n", j * WORD + k + (i)*MIL);
		}
		free(occur);
	}

	return 0;
}