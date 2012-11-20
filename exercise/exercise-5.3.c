/*
 * sum = 1 + 3 + 5 +...+99
 *
 */

#include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i = 0; i < 100; i += 2)
		sum += i;

	printf("sum = %d\n", sum);

	return 0;
}
