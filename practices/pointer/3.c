#include <stdio.h>

int main(int argc, const char *argv[])
{
	int x = 10;
	int *p = &x;

	printf("x address is %p\n", &x);
	printf("x value is %d\n", x);
	printf("p address is %p\n", &p);
	printf("p value is %d\n", p);
	printf("p value is %p\n", p);
	printf("x take up %d bytes in memory\n", sizeof(x));
	printf("p take up %d bytes in memory\n", sizeof(p));

	return 0;
}
