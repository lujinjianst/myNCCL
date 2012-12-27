#include <stdio.h>
#include <stdlib.h>

void print(int, int, int);
int get_calendar(int, int);
int main(int argc, const char *argv[])
{
	int y;
	int m;
	int d;

	printf("please input tod's date(2012/03/04):\n");
	scanf("%d/%d/%d", &y, &m, &d);

//	printf("y: %d\t m: %d\t d:%d\n", y, m, d);

	print(y, m, d);
	get_calendar(y, m);
	return 0;
}

int leap(int y)
{
	if ((y % 4 == 0 && y % 100 != 0)||y % 400 == 0)
		return 1;

	return 0;
}

int get_calendar(int y, int m)
{
	int w;

	w = (y + (y-1)/4 - (y-1)/100 + (y-1)/400) % 7;
	int days = 0;
	switch(m)
	{
		case 12:days+=30;break;
		case 11:days+=31;break;
		case 10:days+=30;break;
		case 9:days+=31;break;
		case 8:days+=31;break;
		case 7:days+=30;break;
		case 6:days+=31;break;
		case 5:days+=30;break;
		case 4:days+=31;break;
		case 3:if(leap(y))days+=29;
		       else days+=28;break;
		case 2:days+=31;break;
		case 1:days+=0;break;
		default:break;
	}
	w = (w + days -1) % 7;
	
	return w;
}

void print(int y, int m, int d)
{
	int w = get_calendar(y, m);

//	printf("%d y %d m %d d is %d\n\n",y, m, d, w );
	printf("%d y %d m   monthly calendar form:\n",y, m);
	printf("\n=======================================================================\n");
	int month[12] = {31,28,31,30,31,30,31,30,31,31,30,31};
	if (leap(y))
		month[1] = 29;
	printf("SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
	int i, j;
	for (i = 0; i < w; i++)
		printf("\t");
		
	for (i = w, j = 1; j <= month[m-1]; i++, j++)
	{
		if (i % 7 == 0)
			printf("\n");
		printf("%d\t", j);
	}
	printf("\n=======================================================================\n");
}


