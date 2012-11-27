#include <stdio.h>

#define N 5

int main(int argc, char *argv[])
{
	int i, j, tmp;
	int arr[N][N] = {{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10},
		{11, 12, 13, 14, 15}, 
		{16, 17, 18, 19, 20}, 
		{21, 22, 23, 24, 25}};
#if 1
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)	
		{
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
	printf("***********************************\n");
#endif
	for(i = 0; i < N - 1; i++)
	{
		for(j = i + 1; j < N; j++)
		{
			tmp = arr[i][j];
			arr[i][j] = arr[j][i];
			arr[j][i] = tmp;
		}
	}

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)	
		{
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
