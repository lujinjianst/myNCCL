#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3

void main_interface();
void find_interface();

void choice(long sno[], char sname[][20], int sage[], float cs[], int N);
void find_choice(long sno[], char sname[][20], int sage[], float cs[], int N);
void input(long sno[], char sname[][20], int sage[], float cs[], int N);
void output(long sno[], char sname[][20], int sage[], float cs[], int N);
void sno_find(long sno[], char sname[][20], int sage[], float cs[], int N);
void sname_find(long sno[], char sname[][20], int sage[], float cs[], int N);
void cs_sort(long sno[], char sname[][20], int sage[], float cs[], int N);
void total(long sno[], char sname[][20], int sage[], float cs[], int N);


int main(int argc, const char *argv[])
{
	long sno[M];
	char sname[M][20];
	int sage[M];
	float cs[M];
	int i, j;

	main_interface();

	choice(sno, sname, sage, cs, M);
	return 0;
}

void main_interface()
{
	printf("\t\t*********************************************************************************\n");
	printf("\t\t*\t\tWelcome to use the system of managing student\t\t\t*\n");
	printf("\t\t*1.input students's basic information	2.output students's information\t\t*\n");
	printf("\t\t*3.find students's basic information	4.sort\t\t\t\t\t*\n");
	printf("\t\t*5.statistics 				0.quit\t\t\t\t\t*\n");
	printf("\t\t*********************************************************************************\n");
	printf("\t\t Please input (0~5):");
	printf("\n");
}
void find_interface()
{
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\tWelcome to use search operation\t\t*\n");
	printf("\t\t*1.According to the student id to find\t\t\t*\n");
	printf("\t\t*2.According to the student name to find\t\t*\n");
	printf("\t\t*0.Return to the previous menu\t\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("Please input (0~2)");
	printf("\n");
}
void choice(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int m;
	while (1)
	{
		scanf("%d", &m);
		switch (m)
		{
			case 1:
				input(sno, sname, sage, cs, N);
				main_interface();
				break;
			case 2:
				output(sno, sname, sage, cs, N);
				main_interface();
				break;
			case 3:
				find_interface();
				find_choice(sno, sname, sage, cs, N);
				main_interface();
				break;
			case 4:
				cs_sort(sno, sname, sage, cs, N);
				break;
			case 5:
				total(sno, sname, sage, cs, N);
				main_interface();
				break;
			case 0:
				exit(1);
			default:
				break;
		}
	}
}

void find_choice(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int m;
	while (1)
	{
		scanf("%d", &m);
		switch (m)
		{
			case 1:
				sno_find(sno, sname, sage, cs, N);
				find_interface();
				break;
			case 2:
				sname_find(sno, sname, sage, cs, N);
				find_interface();
				break;
			case 0:
				break;
		}
		if (0 == m)
			break;
	}

	main_interface();
		
}
void input(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i;
	printf("input %d student's information\n", N);

	for (i = 0; i < N; i++)
	{
		printf("input %dth student's\n",i + 1);
		printf("student id:");
		scanf("%ld", &sno[i]);
		getchar();

		printf("name:");
		gets(sname[i]);

		printf("age:");
		scanf("%d", &sage[i]);

		printf("score:");
		scanf("%f", &cs[i]);
	}
}

void output(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i;

	printf("output %d student's information\n", N);
	for (i = 0; i < N; i++)
	{
		printf("%-10ld", sno[i]);
		printf("%-16s", sname[i]);
		printf("%-4d", sage[i]);
		printf("%-6.0f", cs[i]);
		printf("\n");
	}

}

void sno_find(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i;
	long sno1;

	printf("Please input you want to find student id:");
	scanf("%ld", &sno1);
	
	for (i = 0; i < N; i++)
	{
		if (sno[i] == sno1)
			break;
	}

	if (i < N)
	{
		
		printf("output %d student's information\n", sno1);
		printf("%-10ld", sno[i]);
		printf("%-16s", sname[i]);
		printf("%-4d", sage[i]);
		printf("%-6.0f", cs[i]);
		printf("\n");		
	}

	else 
		printf("The student id you entered does not exist!\n");

}

void sname_find(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i; 
	char sname1[20];

	printf("Please input you want to find name:");
	getchar();
	gets(sname1);

	for (i = 0; i < N; i++)
	{
		if (strcmp(sname[i], sname1) == 0)
			break;
	}
	if (i < N)
	{
		
		printf("output %d student's information\n", sname1);
		printf("%-10ld", sno[i]);
		printf("%-16s", sname[i]);
		printf("%-4d", sage[i]);
		printf("%-6.0f", cs[i]);
		printf("\n");		
	}

	else 
		printf("The student name you entered does not exist!\n");
}

void cs_sort(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i, j, k;
	long tsno;
	char tsname[20];
	int tsage;
	float tcs;

	for (i = 0; i < N - 1; i++)
	{
		k = i;
		for (j = i + 1; j < N; j++)
		{
			if (cs[j] > cs[k])
				k = j;
		}

		if (k != i)
		{
			tsno = sno[i];
			sno[i] = sno[k];
			sno[k] = tsno;

			strcpy(tsname, sname[i]);
			strcpy(sname[i], sname[k]);
			strcpy(sname[k], tsname);

			tsage = sage[i];
			sage[i] = sage[k];
			sage[k] = tsage;

			tcs = cs[i];
			cs[i] = cs[k];
			cs[k] = tcs;

		}
	}
}

void total(long sno[], char sname[][20], int sage[], float cs[], int N)
{
	int i;

	printf("\n excellent(score >= 90) student:\n");

	for (i = 0; i < N; i++)
	{
		if (cs[i] >= 90)
		{
			printf("%-10ld", sno[i]);
			printf("%-16s", sname[i]);
			printf("%-4d", sage[i]);
			printf("%-6.0f", cs[i]);
			printf("\n");	
		}
	}

	printf("\n well(score >= 80 && score < 90) student:\n");
	for (i = 0; i < N; i++)
	{
		if (cs[i] >= 80 && cs[i] < 90)
		{
			printf("%-10ld", sno[i]);
			printf("%-16s", sname[i]);
			printf("%-4d", sage[i]);
			printf("%-6.0f", cs[i]);
			printf("\n");	
		}
	}

	printf("\n medium(score >= 70 && score < 80) student:\n");

	for (i = 0; i < N; i++)
	{
		if (cs[i] >= 70 && cs[i] < 80)
		{
			printf("%-10ld", sno[i]);
			printf("%-16s", sname[i]);
			printf("%-4d", sage[i]);
			printf("%-6.0f", cs[i]);
			printf("\n");	
		}
	}

	printf("\n pass(score >= 60 && score < 70) student:\n");

	for (i = 0; i < N; i++)
	{
		if (cs[i] >= 60 && cs[i] < 70)
		{
			printf("%-10ld", sno[i]);
			printf("%-16s", sname[i]);
			printf("%-4d", sage[i]);
			printf("%-6.0f", cs[i]);
			printf("\n");	
		}
	}
	printf("\n fail(score < 60) student:\n");

	for (i = 0; i < N; i++)
	{
		if (cs[i] < 60)
		{
			printf("%-10ld", sno[i]);
			printf("%-16s", sname[i]);
			printf("%-4d", sage[i]);
			printf("%-6.0f", cs[i]);
			printf("\n");	
		}
	}
}




