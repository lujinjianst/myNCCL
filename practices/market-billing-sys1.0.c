#include <stdio.h>

int main(int argc, const char *argv[])
{
	int num;
	double price;
	double discount;

	printf("Supermarket billing system version 1.0\n");

	printf("Please enter number of Goods\n");
	scanf("%d", &num);

	printf("Please enter price of Goods\n");
	scanf("%lf", &price);

	printf("Please enter discount of Goods\n");
	scanf("%lf", &discount);

	printf("hello, The goods you deal with: %0.1f dollar\n", num * price * discount);

	return 0;
}
