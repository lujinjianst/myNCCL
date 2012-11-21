/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月02日 10时03分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data
{
	int number;
	char name[20];
	int score;

	struct data *next;
};

typedef struct data V_STU;

V_STU *add_one_node(V_STU *head, V_STU *p)
{
	if((head == NULL)||(head->number > p->number))
	{
		p->next = head;
		return p;
	}
	V_STU *ptr = head;

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

V_STU *delete_one_node(V_STU *head, int num)
{
	if(head == NULL)
	{
		puts("empty.");
		return NULL;
	}

	V_STU *p = head;

	if(head->number == num)
	{
		head = head->next;
		free(p);
		return head;
	}
	V_STU *ptr = NULL;
	while(p->next != NULL)
	{
		if(p->next->number == num)
		{
			ptr = p->next;
			p->next = p->next->next;
			free(ptr);
			return head;
		}
		p = p->next;
	}
	puts("No this node");

	return head;

}

int menu(void)
{
	int choice;

	puts("1.print\t2.add\t3.delete\t4.save\t5.quit\n");
	scanf("%d", &choice);
	getchar();

	return choice;
}

void print_list_num(V_STU *p)
{
	printf("\nnum\tname\tscore\n");
	while(p != NULL)
	{
		printf("%d\t%s\t%d\n", p->number, p->name, p->score);
		p = p->next;
	}
	putchar('\n');
}

V_STU *add_to_newh(V_STU *head, V_STU *p)
{
	if((head == NULL)||(head->score > p->score))
	{
		p->next = head;
		return p;
	}
	V_STU *ptr = head;

	while(ptr->next != NULL)
	{
		if(ptr->next->score > p->score)
		{
			break;
		}
		ptr = ptr->next;
	}
	p->next = ptr->next;
	ptr->next = p;

	return head;
}

void destroy(V_STU *p)
{
	V_STU *ptr = NULL;
	while(p != NULL)
	{
		ptr = p;
		p = p->next;
		free(ptr);
	}
}
void print_list_score(V_STU *oldh)
{
	V_STU *newh = NULL;
	V_STU *p = NULL;

	while(oldh != NULL)
	{
		p = malloc(sizeof(V_STU));
		if(p==NULL)
		{
			perror("malloc");
			exit(1);
		}
		p->number = oldh->number;
		strcpy(p->name, oldh->name);
		p->score = oldh->score;
		newh = add_to_newh(newh, p);
		oldh = oldh->next;
	}
	print_list_num(newh);
	destroy(newh);
}
void print_list(V_STU *p)
{
	puts("print in the order of ");
	puts("1.number\t2.score\n");

	int choice;

	scanf("%d", &choice);
	getchar();
	if(choice == 1)
	{
		print_list_num(p);
	}
	else
	{
		print_list_score(p);
	}
	
}
V_STU *add_one_to_link(V_STU *head)
{
	V_STU *p = NULL;
	while(1)
	{
		p = malloc(sizeof(V_STU));
		if(p == NULL)
		{
			perror("malloc");
			exit(1);
		}
		char buf[64];
		puts("Please input number:(press # to quit)");
		scanf("%s", buf);
		getchar();
		if(buf[0] == '#')
		{
			free(p);
			return head;
		}
		p->number = atoi(buf);
		puts("Please input name:");
		scanf("%s", p->name);
		getchar();
		puts("Please input score:");
		scanf("%d", &p->score);
		getchar();

		head = add_one_node(head, p);
	}
	return head;
	

}

V_STU *delete_one_from_link(V_STU *head)
{
	int num = 0;
	char buf[64];

	while(1)
	{
		puts("Please input the number to delete:");
		puts("(press # to quit)");
		scanf("%s", buf);
		getchar();
		if(buf[0] == '#')
		{
			return head;
		}
		num = atoi(buf);
		head = delete_one_node(head, num);
	}
	return head;
}

void save_to_file(V_STU *p)
{
#if 0
	FILE *fp = fopen("stu1", "w+");
	if(fp == NULL)
	{
		perror("stu1");
		exit(1);
	}
	while(p != NULL)
	{
		fprintf(fp, "%d %s %d\n", p->number, p->name, p->score);
		p = p->next;
	}		
	fclose(fp);
#endif

#if 1
	FILE *fp = fopen("stu1", "w+");
	if(fp == NULL)
	{
		perror("stu1");
		exit(1);
	}
	while(p != NULL)
	{
		fwrite(p, sizeof(V_STU), 1, fp);
		p = p->next;
	}		
	fclose(fp);

#endif
}

V_STU *read_info(void)
{
#if 0
	FILE *fp = fopen("stu1", "r");
	if(fp == NULL)
	{
		perror("stu1");
		exit(1);
	}
	V_STU *head = NULL;
	V_STU *p = NULL;

	p = malloc(sizeof(V_STU));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	while(fscanf(fp, "%d %s %d", &p->number, p->name, &p->score) != EOF)
	{
		head = add_one_node(head, p);
		p = malloc(sizeof(V_STU));
		if(p == NULL)
		{
			perror("malloc");
			exit(1);
		}
	}
	free(p);
	fclose(fp);

	return head;
#endif
#if 1
	FILE *fp = fopen("stu1", "r");
	if(fp == NULL)
	{
		perror("stu1");
		exit(1);
	}
	V_STU *head = NULL;
	V_STU *p = NULL;

	p = malloc(sizeof(V_STU));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	while(!feof(fp))
	{
		fread(p, sizeof(V_STU), 1, fp);
		head = add_one_node(head, p);
		p = malloc(sizeof(V_STU));
		if(p == NULL)
		{
			perror("malloc");
			exit(1);
		}
	}
	free(p);
	fclose(fp);

	return head;

#endif
}
int main(void)
{
	V_STU *head = NULL;


	head = read_info();
	char flg = 0;
	while(!flg)
	{
		switch(menu())
		{
		case 1 : print_list(head); break;
		case 2 : head=add_one_to_link(head);break;
		case 3 : head=delete_one_from_link(head);break;
		case 4 : save_to_file(head);break;
		case 5 : flg = 1;break;
		default : break;
		}
	}

	return 0;
}

















