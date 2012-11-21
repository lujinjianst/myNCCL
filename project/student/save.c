#include <stdio.h>
#include "linkedlist.h"
void save_to_file(STU *p)
{
	FILE *fp = fopen("stu1", "w+");
	if (fp ==NULL)
	{
		perror("stu1");
		exit(1);
	}
	while (p != NULL)
	{
		fprintf(fp, "%d %s %d\n",p->number, p->name, p->score);
		p = p->next;
	}	
	fclose(fp);
}
