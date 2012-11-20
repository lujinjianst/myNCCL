#include <stdio.h>

int main(void)
{
	int year, leap_year;

	printf("Enter a year:");
	scanf("%d", &year);

	if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		leap_year = 1;
	else
		leap_year = 0;

	printf("leap_year:%d\n", leap_year);

	return 0;
}
