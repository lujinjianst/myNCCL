#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int N = 19;
	int matrix[N][N];
	int row, col;
	int i, m, n;

	printf("Please enter the odd order rubik's cube matrix order number N(N <= 19):\n");
	scanf("%d", &N);

	if ((N > 10) || (N % 2 == 0))
	{
		printf("input error, N must be odd and N<=19\n");
		exit(0);
	}

	for (row = 0; row < N; row++)
	{
		for (col = 0; col < N; col++)
		{
			matrix[row][col] = 0;
		}
	}

	row = 0; 
	col = (N - 1) / 2;
	matrix[row][col] = 1;

	for (i = 2; i <= N * N; i++)
	{
		int r , c;

		r = row;
		c = col;
		row = (row + N - 1) % N;
		col = (col + N + 1) % N;

		if (0 == matrix[row][col])
			matrix[row][col] = i;
		else
		{
			r = (r + 1) % N;
			matrix[r][c] = i;
			row = r;
			col = c;
		}
		
	}

	printf("\n %d\n", N);

	for (m = 0; m <= N; m++)
		printf("=====");
	printf("\n");

	for (m = 0; m < n; m++)
	{
		for (n = 0; n < N;  n++)
			printf("%4d", matrix[m][n]);
		printf("\n");
	}

	for (m = 0; m <= N; m++)
		printf("=====");
	printf("\n");
	return 0;

}
