#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define QUERY  2
#define UPDATE 3
#define DELETE 4
#define LIST   5
#define QUIT   0 

FILE *fp;

struct Node
{
	char name[100];		//students' name
	char addr[100];		//students' address
	char phone[100];	//students' telephone
	char workfor[100];	//work unit
	struct Node *next;
};


struct Node *txl, *tail;//txl point to the first classmate, tail point to the end classmate.

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

void init();

int main(int argc, const char *argv[])
{
	int choice;

	init();
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

/* Increase initial classmates information*/

void init()
{
	int i = 0;

	struct Node *p; //Temporary work pointer.
	txl = tail = NULL;

	if ((fp = fopen("tx1.txt", "rb")) == NULL)
	{
		//printf("can't open alumni information tx1.txt, please check on !\n");
		//exit(0);
		last = 0;
	}

	else
	{
		while (!feof(fp))		
		{
			if ((p = (struct Node *)malloc(sizeof(struct Node))) == NULL)
			{
				perror("malloc error");
				exit(0);
			}
			
			if (fread(p, sizeof(struct Node), 1, fp) == 1)
			{
				if (i == 0)
					txl = tail = p;
				i++;
				tail->next = p;
				tail = p;
			}

		}
		p->next = NULL;
		last = i;
	}

	fclose(fp);
}

void save()
{
	struct Node *p = txl;

	if ((fp = fopen("tx1.txt", "wb")) == NULL)
	{
		printf("can't open alumni information tx1.txt, please check on !\n");
		exit(0);
	}

	while (p != NULL)
	{
		if(fwrite(p, sizeof(struct Node), 1, fp) == 1);
			p = p->next;
	}

	fclose(fp);
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
	struct Node *p; // Temporary work pointer.

	if ((p = (struct Node *)malloc(sizeof(struct Node))) == NULL)
	{
		printf("System memory is full already, can't increase classmate information again!\n");
		return;
	}
	printf("deal with increseing......\n");
	printf("name:");
	scanf("%s", p->name);
	printf("address:");
	scanf("%s", p->addr);
	printf("telephone:");
	scanf("%s", p->phone);
	printf("Uint:");
	scanf("%s", p->workfor);
	printf("Increase student success\n");

	if (tail != NULL)
	{
		tail->next = p; //Will the students information to join txl chain table tail.
		tail = tail->next; // tail point to the end student forever.
	}

	else 
	{
		txl  = tail = p; // the first student .

	}

	tail->next = NULL;
	last++; // increase a student success , increased 1.
	save(); //save file 
}

void do_update()
{
	char tname[100];	 //Temporary storage input name.
	int i;
	int find = 0; 		 //Whether the student find.	
	struct Node *p = txl; 	 // Temporary work pointer

	printf("deal with modifying......\n");
	printf("Please input to change the name of the students:");
	scanf("%s", &tname);

	while ((p != NULL) && !find)
	{
		if (!strcmp(tname, p->name))
		{
			find = 1;
			printf("You find classmate information below:\n");
			printf("===============================================================\n");
			printf("name:%s\t", p->name);
			printf("address:%s\t", p->addr);
			printf("telephone:%s\t", p->phone);
			printf("work unit:%s\t\n", p->workfor);
			printf("===============================================================\n");
			
			printf("Please input the revised information:\n");
			printf("\n Please modify:\n");
			printf("name:");
			scanf("%s", p->name);
			printf("address:");
			scanf("%s", p->addr);
			printf("telephone:");
			scanf("%s", p->phone);
			printf("Uint:");
			scanf("%s", p->workfor);

		}
		p = p->next;

	}

	if (!find)
	{
		printf("I'm sorry, name for %s classmates haven't login in the alumni\n", tname);
	}

	else
	{
		printf("Name for %s classmates information has been modified successfully\n", tname);
		save();
	}
	p = NULL;
}

void do_list_all()
{
	struct Node *p = txl; // temporary work pointer

	printf("The classmate alumni have %d student information:\n", last);

	while (p != NULL)
	{
		printf("===============================================================\n");
		printf("name:%s\t", p->name);
		printf("address:%s\t", p->addr);
		printf("telephone:%s\t", p->phone);	
		printf("work unit:%s\t\n", p->workfor);
		p = p->next;
	}
	printf("===============================================================\n");
}

void do_query()
{
	char tname[100];	 //Temporary storage input name.
	int i;
	int find = 0; 		 //Whether the student find.	
	struct Node *p = txl;    // temporary work pointer.

	printf("deal with querying......\n");
	printf("Please input to change the name of the students:");
	scanf("%s", &tname);

	while ((p != NULL) && !find)
	{
		if (!strcmp(tname, p->name))
		{
			find = 1;
			printf("You find classmate information below:\n");

			printf("===============================================================\n");
			printf("name:%s\t", p->name);
			printf("address:%s\t", p->addr);
			printf("telephone:%s\t", p->phone);	
			printf("work unit:%s\t\n", p->workfor);
			printf("===============================================================\n");
		}
		p = p->next;
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
	struct Node *p = txl;    //  temporary work pointer.
	struct Node *pre = txl;
	printf("deal with deleteing......\n");
	printf("Please input to be deleted the name of the students:");
	scanf("%s", &tname);

	while ((p != NULL) && !find)
	{
		if (!strcmp(tname, txl[i].name))
		{
			find = 1;
		//	index = i; 	//Storage to delete classmate subcript position
			break;
		}
		pre = p;
		p = p->next;

	}

	if (!find)
	{
		printf("I'm sorry, name for %s classmates haven't login in the alumni\n", tname);
	}
	else
	{
		if (p == pre)
		{
			txl = NULL;
			last = 0;
		}
		else
		{
			pre->next = p->next;
			last--;
			printf("Name for %s classmates information has been deleted successfully\n", tname);
			save();
		}
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
