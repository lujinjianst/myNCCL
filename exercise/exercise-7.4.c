#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i, j,k, counter, tmp;
	int arr[10];
	srand(time(NULL));
	for (i = 0; i < 10; i++)
		arr[i] = rand() % 100;
	for (i = 0; i <10; i++)
	{
		for(j = i + 1; j < 10; j++)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;

			}
		}
	}
	for (j = 0; j <10; j++)
		printf("%d\t", arr[j]);
		printf("\n");
	printf("***************************************************************************\n");

	for(j = 0; j < 10; j++)
	{
		if(arr[j] % 2 == 0)
		{
			tmp = arr[j];
			for(k = j; k < 9; k++)
			{
				arr[k] = arr[k + 1];
			}
			arr[k] = tmp;
			i--;
		}
		if(++counter == 10)
			break;
	}
	for (j = 0; j <10; j++)
		printf("%d\t", arr[j]);
	printf("\n");

	return 0;
}

