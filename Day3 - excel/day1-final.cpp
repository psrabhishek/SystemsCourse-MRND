/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<ctype.h>
#include<stack>
#include<set>

using namespace std;

#define ROWS 10
#define COLS 10
#define NODE 10

struct cell{
	char formula[10];
};

typedef struct cell Cell;

int precedence(char op){
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

// Function to perform arithmetic operations. 
int applyOp(int a, int b, char op){
	switch (op){
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': if (b == 0){
		printf("Divide by zero not allowed\n");
		return 0;
	}
		return a / b;
	}
}

int get(Cell** sheet, int row, int col)
{
	if (!strcmp(sheet[row][col].formula, ""))
		return 0;

	stack <int> values;
	stack <char> ops;

	int  r, c, temp;
	for (int i = 0; sheet[row][col].formula[i]; i++)
	{
		if (sheet[row][col].formula[i] == ' ') continue;
		if (sheet[row][col].formula[i] >= 'A')
		{
			c = sheet[row][col].formula[i];
			if (c < 'a') c -= 'A';
			else c -= 'a';
			sscanf(sheet[row][col].formula+i+1, "%d", &r);
			r--;

			temp = get(sheet, r, c);
			values.push(temp);
			while (sheet[row][col].formula[i + 1] >= '0' || sheet[row][col].formula[i + 1] ==' ') i++;
		}
		else if (sheet[row][col].formula[i] >= '0')
		{
			sscanf(sheet[row][col].formula + i, "%d", &temp);
			values.push(temp);
			while (sheet[row][col].formula[i + 1] >= '0' || sheet[row][col].formula[i + 1] == ' ') i++;
		}
		else if (sheet[row][col].formula[i] == '('){
			ops.push(sheet[row][col].formula[i]);
		}
		else if (sheet[row][col].formula[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			ops.pop();
		}
		else
		{ 
			while (!ops.empty() && precedence(ops.top())
				>= precedence(sheet[row][col].formula[i])){
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(sheet[row][col].formula[i]);
		}
	}
	while (!ops.empty()){
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

int eval(Cell** sheet, char* formula)
{

	stack <int> values;
	stack <char> ops;

	int res, flag = 1, r, c, temp;
	for (int i = 0; formula[i]; i++)
	{
		if (formula[i] == ' ') continue;
		if (formula[i] >= 'A')
		{
			c = formula[i];
			if (c < 'a') c -= 'A';
			else c -= 'a';
			sscanf(formula + i + 1, "%d", &r);
			r--;

			temp = get(sheet, r, c);
			values.push(temp);
			while (formula[i + 1] >= '0' || formula[i + 1] == ' ') i++;
		}
		else if (formula[i] >= '0')
		{
			sscanf(formula + i, "%d", &temp);
			values.push(temp);
			while (formula[i + 1] >= '0' || formula[i + 1] == ' ') i++;
		}
		else if (formula[i] == '('){
			ops.push(formula[i]);
		}
		else if (formula[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			ops.pop();
		}
		else
		{
			while (!ops.empty() && precedence(ops.top())
				>= precedence(formula[i])){
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(formula[i]);
		}
	}
	while (!ops.empty()){
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

int export(Cell ** sheet, char filename[])
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
			if (!strcmp(sheet[i][j].formula, ""))
				fprintf(fp, "NULL");
			else
				fprintf(fp, "%s", sheet[i][j].formula);
			if (j < COLS - 1)
				fprintf(fp,", ");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}

void import(Cell** sheet, char filename[])
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
	int len;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			fscanf_s(fp, "%s", sheet[i][j].formula, _countof(sheet[i][j].formula));
			len = strlen(sheet[i][j].formula);
			if (sheet[i][j].formula[len - 1] == ',')
				sheet[i][j].formula[len - 1] = '\0';
			if (!strcmp(sheet[i][j].formula, "NULL"))
				sheet[i][j].formula[0] = '\0';
			//strcpy(sheet[i][j].formula, "");
			//if (j < COLS - 1)
				//fscanf_s(fp, "%c", &junk);
		}
		//fscanf_s(fp, "%c", &junk);
	}
	fclose(fp);
}

bool hasCycle(Cell** sheet, int row, int col, set<pair<int, int>> visited)
{
	int  r, c;
	for (int i = 0; sheet[row][col].formula[i]; i++)
	{
		if (sheet[row][col].formula[i] >= 'A')
		{
			c = sheet[row][col].formula[i];
			if (c < 'a') c -= 'A';
			else c -= 'a';
			sscanf(sheet[row][col].formula + i + 1, "%d", &r);
			r--;
			pair<int, int> p(r, c);
			if (visited.find(p) != visited.end())
				return 1;
			visited.insert(p);
			if (hasCycle(sheet, r, c, visited))
				return 1;
			visited.erase(p);
			while (sheet[row][col].formula[i + 1] >= '0' || sheet[row][col].formula[i + 1] == ' ') i++;
		}
	}
	return 0;
}

int main()
{
	Cell** sheet = (Cell**)malloc(sizeof(Cell*)*ROWS);
	int i, j, row, col, save = 0, junk, flag = 0;
	char command[10], filename[256] = "", formula[10];
	for (i = 0; i < ROWS; i++)
		sheet[i] = (Cell*)calloc(sizeof(Cell),COLS);
	set<pair <int, int>> visited;

	while (true)
	{
		printf("> ");
		scanf("%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);

		if (!strcmp(command, "get"))
		{
			while ((col = getchar()) == ' '|| col == '\n');
			if (col < 'a') col -= 'A';
			else col -= 'a';
			scanf("%d", &row);
			row--;
			printf("\n %d\n", get(sheet, row, col));
		}

		if (!strcmp(command, "eval"))
		{
			scanf("%s", formula);
			printf("\n %d\n", eval(sheet,formula));
		}


		else if (!strcmp(command, "set"))
		{
			while ((col = getchar()) == ' '||col=='\n');
			if (col < 'a') col -= 'A';
			else col -= 'a';
			scanf("%d", &row);
			row--;
			while (getchar() != '=');
			strcpy(formula, sheet[row][col].formula);
			scanf("%s", &sheet[row][col].formula);
			
			visited.clear();
			if(hasCycle(sheet, row, col, visited))
			{
				printf("There is a cyclic dependency with this formula\n");
				strcpy(sheet[row][col].formula, formula);
			}
			else
			{
				save = 1;
			}
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
					printf("%6d", get(sheet,i,j));
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
				scanf("%c",&junk);
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
				printf("NO file found, please enter filename\t");
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
				scanf("%c",&s);
				scanf("%c", &s);
				if (s == 'Y' || s == 'y')
				{
					printf("enter the file name\t");
					scanf("%s", &filename);
					while((x=export(sheet, filename))!=0);
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
}
*/