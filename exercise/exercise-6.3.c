#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, j, k;
	int n;

	printf("please enter a odd number:");

	while (scanf("%d", &n))
		if (n & 1)
			break;

	k = n / 2;
	printf("k = %d\n", k);

	for (i = -k; i <= k; i++)
	{
		if (i < 0)
			for (j = 0; j < i + k + 1; j++)
				printf("*");
		else
			for (j = 0; j <-i + k + 1; j++)
				printf("*");
		printf("\n");
	}

	return 0;
}
