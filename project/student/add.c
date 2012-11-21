#include <stdio.h>
#include "linkedlist.h"

STU *add_one_node(STU *head, STU *p)
{
	if((head == NULL)||(head->number > p->number))
	{			
		p->next = head;
		return p;
	}
	STU *ptr = head;

	while(ptr->next != NULL)
	{
		if(ptr->next->number > p->number)
		{
			break;	
		}
		ptr = ptr->next;
	}
	p->next = ptr->next;
	ptr->next = p;

	return head;
}

STU *add_one_to_link(STU *head)
{
	STU *p =NULL;
	while(1)
	{
		p = malloc(sizeof(STU));
		if (p == NULL)
		{
			perror("malloc");
			exit(1);
		}
		char buf[64];
		puts("please input number:(enter # to quit!)");
		scanf("%s",buf);
		getchar();
		if (buf[0] == '#')
		{
			free(p);
			return head;
		}
		p->number = atoi(buf);
		puts("input name:");
		fgets(p->name, 20, stdin);
		p->name[strlen(p->name) - 1] = '\0';
		puts("input score:");
		scanf("%d",&p->score);
		getchar();

		head = add_one_node(head, p);
	}	
	return head;
	
}




















