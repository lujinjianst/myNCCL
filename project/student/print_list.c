#include <stdio.h>
#include "linkedlist.h"

STU *add_to_newh(STU *head, STU *p)
{
	if((head == NULL)||(head->score > p->score))
	{
		p->next = head;
		return p;
	}
	STU *ptr = head;

	while(ptr->next != NULL)
	{
		if(ptr->next->score < p->score)
		{
			ptr = ptr->next;
		}
	}

	p->next = ptr->next;
	ptr->next = p;

	return head;
}
void destroy(STU *p)
{
	STU *ptr = NULL;
	while (p != NULL)
	{
		ptr = p;
		p = p->next;
		free(ptr);
	}
}

void print_list_num(STU *p)
{
	printf("\nnumber\tname\tscore\n");
	while (p != NULL)
	{
		printf("%d\t%s\t%d\n",p->number,p->name, p->score);
		p = p->next;
	}
	printf("\n");
}

void print_list_score(STU *oldh)
{
	STU *newh = NULL;
	STU *p = NULL;

	while(oldh != NULL)
	{
		p = malloc(sizeof(STU));
		if (p == NULL)
		{
			perror("malloc");
			exit(1);
		}
		p->number = oldh->number;
		strcpy(p->name,oldh->name);
		p->score = oldh->score;
		newh = add_to_newh(newh, p);
		oldh = oldh->next;
	}
	print_list_num(newh);
	destroy(newh);

}

void print_list(STU *p)
{
	puts("print in the order of :");
	puts("1.number\t2.score\n");
	
	int choice;

	scanf("%d",&choice);
	getchar();
	if (choice == 1)
	{
		print_list_num(p);
	}

	else
	{
		print_list_score(p);
	}

}

