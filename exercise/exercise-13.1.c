#include <stdio.h>

int main(void)
{
	int grade;
	int flag;

	printf("Please input a grade(0--100):");
	scanf("%d", &grade);

	if(grade > 100 || grade < 0)
	{
		printf("Out of range!\n");
		return 1;
	}

	flag = grade / 10;

	switch(flag)
	{
		case 10:
		case 9: printf("A\n"); break;
		case 8: printf("B\n"); break;
		case 7: printf("C\n"); break;
		case 6: printf("D\n"); break;
		default: printf("not pass!\n"); break;
	}

	return 0;
}
