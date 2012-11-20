#include <stdio.h>

int a;
int b;

int main(void)
{
	a = 1;
	b = 2;
	int c = 3;
	int d = 4;

	printf("%p:%d\n", &a, a);
	printf("%x:%d\n", &a, a);
	printf("%p:%d\n", &b, b);
	
	printf("%p:%d\n", &c, c);
	printf("%x:%d\n", &c, c);
	printf("%p:%d\n", &d, d);

	return 0;
}
