#include <stdio.h>
#include "linkedlist.h"

STU *delete_one_node(STU *head, int num)
{
	if (head == NULL)
	{			
		puts("empty");
		return NULL;
	}
	STU *p = head;

	if (head->number == num)
	{
		head = head->next;
		free(p);
		return head;
	}
	STU *ptr = NULL;
	while (p->next != NULL)
	{
		if (p->next->number == num)
		{
			ptr = p->next;
			p->next = p ->next->next;
			free(ptr);
			p =head;
		}
		p = p->next;
	}
		
	if (p->next == NULL)		
	{
		puts("NO this node!");		
	}

	return head;
}
STU *delete_one_from_link(STU *head)
{
	int num = 0;
	char buf[64];

	while (1)
	{		
		puts("Please input number to delete:(press # to quit)");
		scanf("%s",buf);
		getchar();
		if (buf[0] == '#')
		{
			return head;
		}
		num = atoi(buf);
		head = delete_one_node(head, num);
	}

	return head;
}




















