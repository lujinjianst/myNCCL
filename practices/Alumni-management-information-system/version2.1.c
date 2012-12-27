#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define QUERY  2
#define UPDATE 3
#define DELETE 4
#define LIST   5
#define QUIT   0 

typedef struct
{
	char name[100];		//students' name
	char addr[100];		//students' address
	char phone[100];	//students' telephone
	char workfor[100];	//work unit
} TX;

TX txl[100];	// An array of alumni record, Up to one hundred students
int last = 0;	//The current number of alumni

void show_menu();
void do_choice(int);
int get_choice();
void do_quit();
void do_insert();
void do_update();
void do_query();
void do_delete();

void do_list_all();

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
		//Sleep 5 sec, let the user see clearly
		sleep(3);	
	//	system("pause>nul");
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
	printf("\t5. List all students information\n");
	printf("\t0. Quit system\n");
	printf("=============================================\n");
	printf("Please input your choice(0~5):\n");
}

void do_quit()
{
	printf("\n Welcome to use this system again, goodbye!\n");
	exit(0);
}

void do_insert()
{
	printf("deal with increseing......\n");
	printf("name:");
	scanf("%s", &txl[last].name);
	printf("address:");
	scanf("%s", &txl[last].addr);
	printf("telephone:");
	scanf("%s", &txl[last].phone);
	printf("Uint:");
	scanf("%s", &txl[last].workfor);
	printf("Increase student success\n");
	last++; // increase a student success , increased 1.
}

void do_update()
{
	char tname[100];	 //Temporary storage input name.
	int i;
	int find = 0; 		 //Whether the student find.	

	printf("deal with modifying......\n");
	printf("Please input to change the name of the students:");
	scanf("%s", &tname);

	for (i = 0; i < last && !find; i++)
	{
		if (!strcmp(tname, txl[i].name))
		{
			find = 1;
			printf("You find classmate information below:\n");
			printf("name:%s\t", txl[i].name);
			printf("address:%s\t", txl[i].addr);
			printf("telephone:%s\t", txl[i].phone);
			printf("work unit:%s\t", txl[i].workfor);

			printf("\n Please modify:\n");
			printf("name:");
			scanf("%s", &txl[i].name);
			printf("address:");
			scanf("%s", &txl[i].addr);
			printf("telephone:");
			scanf("%s", &txl[i].phone);
			printf("Uint:");
			scanf("%s", &txl[i].workfor);

		}
		
	}

	if (!find)
	{
		printf("I'm sorry, name for %s classmates haven't login in the alumni\n", tname);
	}

	else
	{
		printf("Name for %s classmates information has been modified successfully\n", tname);
	}
}

void do_list_all()
{
	int i;

	printf("The classmate alumni have %d student information:\n", last);

	for (i = 0; i < last; i++)
	{
		printf("===============================================================\n");
		printf("name:%s\t", txl[i].name);
		printf("address:%s\t", txl[i].addr);
		printf("telephone:%s\t", txl[i].phone);	
		printf("work unit:%s\t\n", txl[i].workfor);

	}
	printf("===============================================================\n");
}

void do_query()
{
	char tname[100];	 //Temporary storage input name.
	int i;
	int find = 0; 		 //Whether the student find.	

	printf("deal with querying......\n");
	printf("Please input to change the name of the students:");
	scanf("%s", &tname);

	for (i = 0; i < last && !find; i++)
	{
		if (!strcmp(tname, txl[i].name))
		{
			find = 1;
			printf("You find classmate information below:\n");
			printf("name:%s\t", txl[i].name);
			printf("address:%s\t", txl[i].addr);
			printf("telephone:%s\t", txl[i].phone);
			printf("work unit:%s\t\n", txl[i].workfor);
		}
		
	}

	if (!find)
	{
		printf("I'm sorry, name for %s classmates haven't login in the alumni\n", tname);
	}
}

void do_delete()
{
	char tname[100];	 //Temporary storage to delete students' name.
	int i;
	int find = 0; 		 //Whether the student find.	
	int index; 		 //Record to be deleted in students of the array index

	printf("deal with deleteing......\n");
	printf("Please input to be deleted the name of the students:");
	scanf("%s", &tname);

	for (i = 0; i < last && !find; i++)
	{
		if (!strcmp(tname, txl[i].name))
		{
			find = 1;
			index = i; 	//Storage to delete classmate subcript position
			break;
		}
		
	}

	if (!find)
	{
		printf("I'm sorry, name for %s classmates haven't login in the alumni\n", tname);
	}
	else
	{
		for (i = index; i <= last; i++)
		{
			strcpy(txl[i].name, txl[i+1].name);
			strcpy(txl[i].addr, txl[i+1].addr);
			strcpy(txl[i].phone, txl[i+1].phone);
			strcpy(txl[i].workfor, txl[i+1].workfor);
		}
		last--;
		printf("Name for %s classmates information has been deleted successfully\n", tname);
	}
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
		case LIST:
			do_list_all();
			break;
		case QUIT:
			do_quit();
			break;
		default:
			break;
	}
}
