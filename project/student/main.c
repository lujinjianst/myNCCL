#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
	STU *head = NULL;
	head = read_info();
	char flg = 0;
	while(!flg)
	{
		switch (menu())
		{
			case 1:print_list(head);break;
			case 2:head = add_one_to_link(head);break;
			case 3:head = delete_one_from_link(head);break;
			case 4:save_to_file(head);break;
			case 5:flg = 1; break;
			default:break;
		}
	}
	return 0;
}
