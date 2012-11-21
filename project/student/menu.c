#include <stdio.h>
#include "linkedlist.h"

int menu(void)
{
	int choice;

	puts("Please select the option:\n");
	puts("1.print_list\n2.add\n3.delete\n4.save\n5.exit");
	scanf("%d",&choice);

	return choice;
}
