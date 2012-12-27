#include <stdio.h>
#include <stdlib.h>

int pscore;
int cscore;
int count ;

void init();
int p_show_fist();
int c_show_fist();
void judge(int, int);
void get_score();

int main(int argc, const char *argv[])
{
	static char con;
	int p_fist;
	int c_fist;

	init();
	scanf("%c", &con);
	fflush(stdin);
	while (con == 'y')
	{
		p_fist = p_show_fist();
		c_fist = c_show_fist();
		judge(p_fist, c_fist);
		count++;
		printf("\nstart the next round(y/n)");
		fflush(stdin);
		scanf("%c", &con);
	}
	printf("hello\n");
	get_score();

	sleep(1);
	return 0;
}

void init()
{
	pscore = 0;
	cscore = 0;
	count = 0;

	printf("-------------------welcome to game world----------------------\n");
	printf("\n\t\t*********************************\n");
	printf("\t\t***finger-guessing-game, start **\n");
	printf("\t\t********************************\n");
	printf("\n\nThrow a punch rules: 1.scissor 2.rock 3.cloth \n");
	printf("\n**************************************************************\n");
	printf("\nTO start? (y / n)");
}

int c_show_fist()
{
	int show ;

	srand(time(NULL));
	show = rand() % 3 + 1;

	switch(show)
	{
		case 1:
			printf("\n computer throw a punch: scissor\n");
			break;
		case 2:
			printf("\n computer throw a punch: rock\n");
			break;
		case 3:
			printf("\n computer throw a punch: cloth\n");
			break;
		default:
			break;
	}

	return show;
}

int p_show_fist()
{
	int show ;

	printf("\nplease throw a punch:1.scissor 2. rock 3. cloth (enter a correspending number):\n");
	scanf("%d", &show);

	switch(show)
	{
		case 1:
			printf("\n you throw a punch: scissor\n");
			break;
		case 2:
			printf("\n you throw a punch: rock\n");
			break;
		case 3:
			printf("\n you throw a punch: cloth\n");
			break;
		default:
			break;
	}

	return show;
}

void judge(int p_fist, int c_fist)
{
	if ((p_fist == 1 && c_fist == 1) || (p_fist == 2 && c_fist == 2) || (p_fist == 3 && c_fist == 3))
		printf("\n result:ties, Bummer!\n");
	else if ((p_fist == 1 && c_fist == 3) || (p_fist == 2 && c_fist == 1) || (p_fist == 3 && c_fist == 2))
	{
		printf("\n result: congratulation, you win\n");
		pscore++;
	}
	else
	{
		printf("\n result: ^_^, you failed, foolish!\n");
		cscore++;
	}
}

void get_score()
{
	int result;

	printf("\n----------------------------------------------");
	printf("\nfight %d times, you win %d times, tie %d times, fail %dtimes\n", count, pscore, count - pscore - cscore, cscore);
	printf("\n----------------------------------------------");

	if (pscore == cscore)
		result = 1;
	else if (pscore > cscore)
		result = 2;
	else 
		result = 3; 


	if (result == 1)
		printf("result:ties , and next time \n");
	else if (result == 2)
		printf("result: congratulate to you !\n");
	else
		printf("result : benben, come on again\n");
}
