#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create(int *s)
{
	srand(time(NULL));
	*s = rand() % 100 + 1;
}

void guess(int s)
{
	int count = 1;
	int num;
	while(1)
	{
		printf("Enter a number 0 ~ 100:\n");
		scanf("%d", &num);
		if(num == s)
		{
			printf("Yes! you are ringt!!!\n");
			printf("Guess-- %d --times~~\n", count);
			break;
		}
		if(num < s)
			printf("less!\n");
		else if(num > s)
			printf("more!\n");
		count++;
	}
}
int main(void)
{
	int secret;
	create(&secret);
	guess(secret);
	return 0;
}
