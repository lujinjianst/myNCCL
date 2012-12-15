#include <stdio.h>

int main(int argc, const char *argv[])
{
	int pcount;
	int cnum;
	int pnum;

	printf("\t Guessing number game\n");

	// 1.The computer random generation number
	srand(time(NULL));
	cnum = rand() % 100 + 1;

	// 2.Player stays begining to guess until guessing is right, recording the pcount which is guessing's count
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

	// 3.According to the number of speculation evaluation
	if (pcount <= 2)
		printf("oh, my god , you guess %d times \n", pcount);
	else if (pcount <= 5)
		printf("you just have too, you guess %d times \n", pcount);
	else if (pcount <= 8)
		printf("Good luck , you guess %d times \n", pcount);
	else
		printf("you are foolish you guess %d times\n", pcount);

	return 0;
}
