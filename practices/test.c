#include <stdio.h>

int x  = 20;

void test()
{
	int x = 30;
	printf("x= %d\n", x);
}

void test1()
{
	static int x = 10;
	int y = 10;

	printf("x= %d\ty= %d\n", x, y);
	x = x + 10;
	y = y + 10;
}
#if 0
int main(int argc, const char *argv[])
{
//	test();
//	printf("x= %d\n", x);
	test1();	
	test1();	
	test1();	
	return 0;
}
#endif
int main(int argc, const char *argv[])
{
	register int i;
	for (i = 1; i <= 10; i++)
		printf("%d\n", i);
	return 0;
}
