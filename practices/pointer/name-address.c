#include <stdio.h>

int main(int argc, const char *argv[])
{
	int x = 10;
	printf("x address is %p\n", &x);
	printf("x value is %d\n", x);
	printf("x take up %d bytes in memory\n", sizeof(x));

	return 0;
}
