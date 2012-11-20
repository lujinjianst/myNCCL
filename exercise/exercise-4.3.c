#include <stdio.h>

int main(void)
{
	int num;
	int mid_row, i;
	int row;

	printf("Please input a num:");
	scanf("%d", &num);

	if(num % 2 == 0)
	{
		printf("num is an even num!\n");
		return 1;
	}

	mid_row = num / 2;
	printf("mid_row:%d\n", mid_row);

	for(row = 0; row < num; row++)
	{
		if(row <= mid_row)
		{
			for(i = 0; i < 2 * row + 1; i++)
				printf("*");
			printf("\n");
		}
		else
		{
			for(i = 0; i < 2 * (mid_row - (row - mid_row)) + 1; i++ )
				printf("*");
			printf("\n");
		}
	}

	return 0;
}

