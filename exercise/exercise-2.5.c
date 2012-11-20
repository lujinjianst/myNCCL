#include <stdio.h>


int main(int argc, char *argv[])
{
	int i = 0x1ffff;

	printf("%hx\n", (unsigned short)i);

	return 0;
}

