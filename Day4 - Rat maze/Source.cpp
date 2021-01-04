#include<stdio.h>
#include<stdlib.h>
#define ROWS 10
#define COLS 10

bool solve_maze(int** maze, int** sol, int x, int y )
{
	if (x == ROWS - 1 && y == COLS - 1) 
	{
		sol[x][y] = 1;
		return true;
	}

	if (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 1)
	{
		sol[x][y] = 1;

		if (solve_maze(maze, sol, x + 1, y) || solve_maze(maze, sol, x, y + 1))
			return true;

		sol[x][y] = 0;
		return false;
	}
	return false;
}

void test_rat_maze()
{
	int ** maze, ** sol, i, j;
	maze = (int**)malloc(sizeof(int*)*ROWS);
	for (i = 0; i < ROWS; i++)
		maze[i] = (int*)malloc(sizeof(int)*COLS);

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			scanf("%d", &maze[i][j]);

	sol = (int**)malloc(sizeof(int*)*ROWS);
	for (i = 0; i < ROWS; i++)
		sol[i] = (int*)malloc(sizeof(int)*COLS);
	
	printf("enter the starting co-ordinates\n");
	scanf("%d%d", &i, &j);
	solve_maze(maze, sol, i, j);

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			printf(" %d ", sol[i][j]);
		printf("\n");
	}

}


int main()
{
	test_rat_maze();
	return 0;
}