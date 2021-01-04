/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<ctype.h>
#define ROWS 10
#define COLS 10

int export(int ** sheet, char filename[])
{
	FILE* fp;
	int i, j;
	const char* mode = "w";

	if (getchar() != '\n') printf("n");
	if (strcmp(filename + strlen(filename) - 4, ".csv"))
	{
		strcat(filename, ".csv");
	}
	if (fopen_s(&fp, filename, mode) == EINVAL)
	{
		printf("File Doesn't Exist");
		return 1;
	}
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			fprintf(fp, "%d", sheet[i][j]);
			if (j < COLS - 1)
				fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}

void import(int ** sheet, char filename[])
{
	FILE* fp;
	int i, j;
	const char* mode = "r";

	if (getchar() != '\n') printf("n");
	if (strcmp(filename + strlen(filename) - 4, ".csv"))
	{
		strcat(filename, ".csv");
	}
	if (fopen_s(&fp, filename, mode) == EINVAL)
	{
		printf("File Doesn't Exist");
		return;
	}
	char junk;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			fscanf_s(fp, "%d", &sheet[i][j]);
			if (j < COLS - 1)
				fscanf_s(fp, "%c", &junk);
		}
		fscanf_s(fp, "%c", &junk);
	}
	fclose(fp);
}

int main_v1()
{
	int** sheet = (int**)malloc(sizeof(int*)*ROWS);
	int i, j, row, col, save = 0, junk, flag = 0;
	char command[10], filename[256];
	for (i = 0; i < ROWS; i++)
		sheet[i] = (int*)calloc(sizeof(int), COLS);
	while (true)
	{
		printf("> ");
		scanf("%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);
		if (!strcmp(command, "get"))
		{
			while ((col = getchar()) == ' ' || col == '\n');
			if (col < 'a') col -= 'A';
			else col -= 'a';
			scanf("%d", &row);
			row--;
			printf("\n %d\n", sheet[row][col]);
		}
		else if (!strcmp(command, "set"))
		{
			while ((col = getchar()) == ' ' || col == '\n');
			if (col < 'a') col -= 'A';
			else col -= 'a';
			scanf("%d", &row);
			row--;

			scanf("%d", &sheet[row][col]);
			if (getchar() != '\n') printf("\n");
			save = 1;
		}
		else if (!strcmp(command, "print"))
		{
			printf("\n   ");
			for (i = 0; i < COLS; i++)
				printf("     %c", i + 'A');
			for (i = 0; i < ROWS; i++)
			{
				printf("\n%2d ", i + 1);
				for (j = 0; j < COLS; j++)
				{
					printf("%6d", sheet[i][j]);
				}
			}
			printf("\n");
		}
		else if (!strcmp(command, "import"))
		{
			scanf("%s", &filename);
			import(sheet, filename);
			flag = 1;
		}
		else if (!strcmp(command, "export"))
		{
			scanf("%s", &filename);
			if (!save && flag)
			{
				printf("Already file exists with same data do you still want to export?(y|n)");
				scanf("%c", &junk);
				if (junk == 'Y' || junk == 'y')
					save = export(sheet, filename);
			}
			save = export(sheet, filename);
			flag = 1;
		}
		else if (!strcmp(command, "save"))
		{
			if (!save)
			{
				printf("NO changes to be saved\n");
				continue;
			}
			if (!strcmp(filename, ""))
			{
				printf("ON file found, please enter filename\t");
				scanf("%s", &filename);
			}
			save = export(sheet, filename);
		}
		else if (!strcmp(command, "exit"))
		{
			char s;
			if (save)
			{
				int x;
				printf("Do you want save changes?(Y?N)");
				scanf("%c", &s);
				scanf("%c", &s);
				if (s == 'Y' || s == 'y')
				{
					printf("enter the file name\t");
					scanf("%s", &filename);
					while ((x = export(sheet, filename)) != 0);
				}
			}
			break;
		}
		else
		{
			printf("Wrong Command \"%s\"\n", command);
		}

	}
	return 0;
}*/