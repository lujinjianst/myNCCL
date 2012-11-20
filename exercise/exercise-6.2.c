/*
 * narcissistic number
 * */

#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;
	int a, b, c;

	for (n = 100; n < 9999; n++)
	{
		a = n / 100;
		b = n %100 / 10;
		c = n % 10;

		if (n == a*a*a + b*b*b + c*c*c)
			printf("narcissistic number is %d\n", n);
	}
	return 0;
}

