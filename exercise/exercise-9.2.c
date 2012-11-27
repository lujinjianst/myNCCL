#include <stdio.h>

void main(void)
{
	int scores[100];
	float salaries[100];
	char string[100];

	printf("Bytes used to hold int scores[100] is %d bytes\n",
			sizeof(scores));

	printf("Bytes used to hold int salaries[100] is %d bytes\n",
			sizeof(salaries));

	printf("Bytes used to hold char string[100] is %d bytes\n",
			sizeof(string));


	printf("\n");

	printf("Address of the array scores is %x &scores is %x\n", 

			scores, &scores);

	printf("Address of the array salaries is %x &count is %x\n", 

			salaries, &salaries);

	printf("Address of the array string is %x &string is %x\n", 

			string, &string);
}

