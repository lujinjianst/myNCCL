#include <stdio.h>

int global = 100;
char global_c ;
short global_s;
float global_f;

int main(void)
{
	printf("global at %p\n", &global);
	printf("(global + 1) at %p\n", &global + 1);

	printf("global at %p\n", &global_c);
	printf("global at %p\n", &global_s);
	printf("global at %p\n", &global_f);
	
	printf("\n");

	printf("global at %p\n", (int)&global_c);
	printf("global at %p\n", (unsigned int)&global_s);
	printf("global at %p\n", (long)&global_f);

	return 0;
}   
