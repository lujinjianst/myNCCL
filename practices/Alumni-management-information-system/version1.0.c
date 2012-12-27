#include <stdio.h>
#include <stdlib.h>

#define INSERT 1
#define QUERY  2
#define UPDATE 3
#define DELETE 4
#define QUIT   0 

void show_menu();
void do_choice(int);
int get_choice();
void do_quit();
void do_insert();
void do_update();
void do_query();
void do_delete();

int main(int argc, const char *argv[])
{
	int choice;

	while (1)
	{
		//1.display the main menu
		show_menu();
		//2.retrieve the user opition
		choice = get_choice();
		//3.According to the function of the corresponding choice of implementation
		do_choice(choice);
		
		system("pause>nul");
	}
	return 0;
}

void show_menu()
{
	system("clear");
	printf("====Alumnni management information system\n");
	printf("\t1. Increase students information\n");
	printf("\t2. Find students information\n");
	printf("\t3. Modify students information\n");
	printf("\t4. Delete students information\n");
	printf("\t0. Quit system\n");
	printf("=============================================\n");
	printf("Please input your choice(0~4):\n");
}

void do_quit()
{
	printf("\n Welcome to use this system again, goodbye!\n");
	exit(0);
}

void do_insert()
{
	printf("deal with increseing......\n");
}

void do_update()
{
	printf("deal with modifying......\n");
}

void do_query()
{
	printf("deal with querying......\n");
}

void do_delete()
{
	printf("deal with deleteing......\n");
}

int get_choice()
{
	int choice;

	scanf("%d", &choice);

	return choice;
}

void do_choice(int choice)
{
	printf("is in the process of the first %d a choice \n", choice);

	switch (choice)
	{
		case INSERT :
			do_insert();
			break;
		case QUERY:
			do_query();
			break;
		case UPDATE:
			do_update();
			break;
		case DELETE:
			do_delete();
			break;
		case QUIT:
			do_quit();
			break;
		default:
			break;
	}
}
