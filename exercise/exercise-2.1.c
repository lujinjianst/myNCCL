#include <stdio.h>

int main(void)
{
	int Item, month, day, year;
	float Price;

	printf("Enter item number:");
	scanf("%d", &Item);

	printf("Enter unit price:");
	scanf("%f", &Price);

	printf("Enter purchase date(mm/dd/yyyy):");
	scanf("%d/%d/%d", &month, &day, &year);

	printf("Item Unit Price Purchase Date\n");
	printf("%d $%.2f %d/%d/%d\n", Item, Price, month, day, year);

	return 0;
}
