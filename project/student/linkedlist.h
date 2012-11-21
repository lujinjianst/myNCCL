#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
struct data
{
	int number;
	char name[20];
	int score;
	struct data *next;
};

typedef struct data STU;

void print_list(STU *p);
void save_to_file();
STU *read_info(void);
STU *add_one_to_link(STU *head);
STU *delete_one_from_link(STU *head);
int menu(void);

#endif





