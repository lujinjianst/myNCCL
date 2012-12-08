#include <stdio.h>
#include <stdlib.h>

#define ON	1
#define OFF	0

struct ctr_type{
	unsigned int tem1;
	float tem2;
	unsigned lmp:5;
	unsigned sw1:1;
	unsigned sw2:1;
	unsigned alm:1;
};

typedef struct ctr_type Ctrol;

void main(void)
{
	void sample(Ctrol *wp);
	void control(Ctrol *wp);

	Ctrol word;
	while (1)
	{
		sample(&word);
		if (word.tem1 >= 300)
		{
			printf("the temperture is too high.\n");
			exit(0);
		}

		word.lmp = ~(0xffff << (int )word.tem1/10);

		if (word.tem2 < 10)
		{
			word.alm = ON;
			word.sw1 = ON;
			word.sw2 = OFF;
		}

		else if (word.tem2 < 40)
			word.sw1 = word.sw2 = word.alm = OFF;

		else
		{
			word.sw1 = OFF;
			word.sw2 = word.alm = ON;
		}
		control(&word);
	}
}

void sample(Ctrol *wp)
{
	printf("\n input test data(0~255) (over 300 for end):");
	scanf("%u", &wp->tem1);
	wp->tem2 = wp->tem1 * 0.2;
}

void control (Ctrol *wp)
{
	char i, m;
	printf("\n%6s %6s %4s %4s %6s", "degree", "lamp", "sw1", "sw2", "alarm");
	printf("\n%6.1f ", wp->tem2);

	for (i = 0, m = 0x10; i < 5; i++, m>>=1)
		printf("%c", wp->lmp&m ?'*':' ');
	printf("%4s", wp->sw1?"ON":"OFF");
	printf("%4s", wp->sw2?"ON":"OFF");
	printf("%4s", wp->alm?"ON\0x07":"OFF\x20");
}
