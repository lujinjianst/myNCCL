#include <stdio.h>
#include "linkedlist.h"

STU *read_info(void)
{
	FILE *fp = fopen("stu1","r");
	if (fp == NULL)
	{
		perror("stu1");
		exit(1);
	}
	STU *head =NULL;
	STU *p = NULL;

	p = malloc(sizeof(STU));
	if (p == NULL)
	{
		perror("malloc");
		exit(1);
	}	
	while (fscanf(fp,"%d %s %d", &p->number, p->name, &p->score) != EOF)
	{
		head = add_one_node(head,p);
		p = malloc(sizeof(STU));
		if (p == NULL)
		{
			perror("malloc");
			exit(1);
		}
	}
	free(p);
	fclose(fp);

	return head;
}
