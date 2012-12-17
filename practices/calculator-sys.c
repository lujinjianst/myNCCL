#include <stdio.h>
#include <stdlib.h>

int get_choice();
void show_menu();
void do_exercise(int);
int test(int);

int main(int argc, const char *argv[])
{
	int choice;
	
	do
	{
		show_menu();

		choice = get_choice();

		if (0 == choice)
		{
			break;
		}

		do_exercise(choice);

		sleep(2);
		system("clear");
	} while (choice != 0);

	printf("\n welcome to use this software, goodbye!\n");
	return 0;
}

int get_choice()
{
	int choice;
	scanf("%d", &choice);

	return choice;
}

void show_menu()
{
	printf("===============================================\n");
	printf("\twelcome to use  calculator-software for pupil\n");
	printf("\t1.Addition Practise       2.Subtration Practise\n");
	printf("\t3.Multiplation Practise   4.Division Practise\n");
	printf("\t5.General Practise        0.Quit System\n");
	printf("===============================================\n");
	printf("Please input your choice(0~5)\n");
}

void do_exercise(int n)
{
	int score = 0;
	int i;

	for(i = 1; i <= 10; i++)
		score = score + test(n);
	printf("This practise ten question you did %d the right thing and way\n", score);
}

int test(int n)
{
	int ranswer;
	int uanswer;
	int t;
	char operator;

	srand(time(NULL));
	int num1 = rand() % 10;
	int num2 = rand() % 10;

	if (5 == n)
		n = rand() % 4 + 1;

	switch(n)
	{
		case 1:
			operator = '+';
			break;
		case 2:
			operator = '-';
			break;
		case 3:
			operator = '*';
			break;
		case 4:
			operator = '/';
			break;
		default:
			break;

	}

	if ((operator == '-') && (num1 < num2))
	{
		t = num1;
		num1 = num2;
		num2 = t;
	}

	if (operator == '/')
	{
		if (num2 == 0)
			num2 = 1;
		num1 = num1 * num2;
	}

	printf("%d %c %d\n", num1, operator, num2);
	scanf("%d", &uanswer);

	switch (operator)
	{
		case '+':
			ranswer = num1 + num2;
			break;
		case '-':
			ranswer = num1 - num2;
			break;
		case '*':
			ranswer = num1 * num2;
			break;
		case '/':
			ranswer = num1 / num2;
			break;
	}

	if (uanswer == ranswer)
	{
		printf("you do it right!\n");
		return 1;
	}

	else 
	{
		printf("you do it default!\n");
		return 0;
	}
}
