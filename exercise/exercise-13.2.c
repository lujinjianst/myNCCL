#include <stdio.h>

char *mon[13] = {"0", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main(int argc, char *argv[])
{
	int day, month, year;

	printf("Enter date(dd/mm/yy):");
	scanf("%d/%d/%d", &day, &month, &year);

	switch(day)
	{
		case 1: case 21: case 31:
			printf("Dated this %dst day of %s,%d\n", day, mon[month], year);
			break;
		case 2: case 22: 
			printf("Dated this %dend day of %s,%d\n", day, mon[month], year);
			break;
		case 3: case 23: 
			printf("Dated this %drd day of %s,%d\n", day, mon[month], year);
			break;
		default:
			printf("Dated this %dth day of %s,%d\n", day, mon[month], year);
			break;
	}

	return 0;
}
