#include <stdio.h>

int main(int argc, const char *argv[])
{
	int num;
	double price;
	double discount;
	double total;

	printf("\tSupermarket billing system version 1.0\n");
	printf("\n==========================================\n");
	do
	{
		printf("Please enter number of Goods\n");
		scanf("%d", &num);

		if (0 == num)
			break;

		printf("Please enter price of Goods\n");
		scanf("%lf", &price);

		printf("Please enter discount of Goods\n");
		scanf("%lf", &discount);

		total += num * price * discount;
		printf("\n");
	} while (num != 0);

	printf("\n================================================\n");
	printf("hello, The goods you deal with: %0.1f dollar\n", total);
	printf("\twelcome to go shopping again!\n");

	return 0;
}
