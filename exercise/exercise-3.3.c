#include <stdio.h>

int main(void)
{
	int counter;
	int sum = 0;

	printf("hello, NCCL!\n");

	counter = 0;
	do 
	{
		counter++;
		printf("counter = %d\n", counter);

		printf("sum = %d\n", sum += counter);
	} while (counter < 10);

	return 0;
}
