#include <stdio.h>

#define ARRAY_SIZE 5

int main(int argc, const char *argv[])
{
	int values[ARRAY_SIZE] = {23, 24, 45, 56, 74};
	int i;

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("values[%d] %d\n", i, values[i]);

	return 0;
}
