#include <stdio.h>

int init()
{
	// 1.The computer random generation number
	srand(time(NULL));
	return (rand() % 100 + 1);
}

int play(int cnum)
{
	int pcount;
	int pnum;
	// 2.Player stays begining to guess until guessing is right, recording the pcount which is guessing's count
	printf("\t Guessing number game\n");
	pcount = 0;
	printf("Please input your guess number(0 ~ 100)\n");
	scanf("%d", &pnum);
	pcount = pcount + 1;
	while (pnum != cnum)
	{
		if (pnum < cnum)
			printf("You guess's number is smaller\n");
		if (pnum > cnum)
			printf("You guess's number is bigger\n");
		scanf("%d", &pnum);
		pcount = pcount + 1;
	}
	return pcount;
}

void get_score(int pcount)
{
	// 3.According to the number of speculation evaluation
	if (pcount <= 2)
		printf("oh, my god , you guess %d times \n", pcount);
	else if (pcount <= 5)
		printf("you just have too, you guess %d times \n", pcount);
	else if (pcount <= 8)
		printf("Good luck , you guess %d times \n", pcount);
	else
		printf("you are foolish you guess %d times\n", pcount);



}

int main(int argc, const char *argv[])
{
	int cnum = init();

	int pcount = play(cnum);

	get_score(pcount);
	return 0;
}
