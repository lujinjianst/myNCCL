#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

int mod(int a, int b)
{
	return a % b;
}

int main(void)
{
	int a, b;
	char flag;

	printf("Please input like this(2 + 3):");
	scanf("%d %c %d", &a, &flag, &b);

	switch(flag)
	{
		case '+': printf("%d %c %d = %d\n", a, flag, b, add(a, b)); break;
		case '-': printf("%d %c %d = %d\n", a, flag, b, sub(a, b)); break;
		case '*': printf("%d %c %d = %d\n", a, flag, b, mul(a, b)); break;
		case '/': printf("%d %c %d = %d\n", a, flag, b, div(a, b)); break;
		case '%': printf("%d %c %d = %d\n", a, flag, b, mod(a, b)); break;
		default: printf("flag error\n"); break;

	}

	return 0;
}
