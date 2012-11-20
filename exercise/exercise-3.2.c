#include <stdio.h>

int main(void)
{
	int counter;

	printf("hello, NCCL!\n");
#if 0 

	counter =  10;
	while (counter > 0)
	{
		counter--;
		printf("counter = %d\n", counter);
	}
#endif

#if 0
	counter = 10;
	do 
	{
		counter--;
		printf("counter = %d\n", counter);
	} while (counter > 0);
#endif

#if 1
	counter = 10;
	while (counter > 0)
	{
		printf("counter = %d\n", counter);
		sleep(1);
		counter++;
	}
#endif
	return 0;
}
