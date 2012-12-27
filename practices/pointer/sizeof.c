#include <stdio.h>

int main(int argc, const char *argv[])
{
	char c = 'a';
	int x = 0;
	long l = 12L;
	float f = 2.0f;
	double d = 3.3;

	printf("sizeof used in constant:\n");
	printf("a take up %d bytes.\n", sizeof('a'));
	printf("1.1232f take up %d bytes.\n", sizeof(1.1232f));
	printf("1232 take up %d bytes.\n", sizeof(1232));
	printf("1.1232 take up %d bytes.\n", sizeof(1.1232));
	printf("\n");

	printf("c take up %d bytes.\n", sizeof(c));
	printf("x take up %d bytes.\n", sizeof(x));
	printf("l take up %d bytes.\n", sizeof(c));
	printf("f take up %d bytes.\n", sizeof(f));
	printf("d take up %d bytes.\n", sizeof(d));
	printf("\n");

	printf("sizeof used in datetype:\n");
	printf("char take up %d bytes.\n", sizeof(char));
	printf("short take up %d bytes.\n", sizeof(short));
	printf("float take up %d bytes.\n", sizeof(float));
	printf("long take up %d bytes.\n", sizeof(long));
	printf("int take up %d bytes.\n", sizeof(int));
	printf("double take up %d bytes.\n", sizeof(double));
	printf("\n");
	
	printf("sizeof used in expression:\n");
	printf("x + 2 take up %d bytes.\n", sizeof(x + 2));
	printf("x + 2.0 take up %d bytes.\n", sizeof(x + 2.0));
	return 0;
}
