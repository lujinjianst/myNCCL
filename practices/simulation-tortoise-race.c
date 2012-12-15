#include <stdio.h>

int main(int argc, const char *argv[])
{
	double tspeed; //tortoise speed
	double rspeed;  //rabbit spee
	double rstime; //rabbit stay time
	double length; //runway length
	double ttime;  //tortoise uses time 
	double rtime;  //rabbit uses time
	
	printf("===================================\n");
	printf("\tSimulation race the tortoise\n");

	printf("Please tortoise's speed\n");
	scanf("%lf", &tspeed);
	printf("Please rabbit's speed\n");
	scanf("%lf", &rspeed);
	printf("rabbit stays how long\n");
	scanf("%lf", &rstime);
	printf("Please enter runway's length\n");
	scanf("%lf", &length);

	ttime = length / tspeed;
	rtime = length / rspeed + rstime;

	printf("===================================\n");
	if (rtime > ttime)
		printf("\nThe game won the tortoise\n");

	else if (rtime < ttime)
		printf("\nThe game won the rabbit\n");

	else
		printf("\noh my god, tortoise and rabbit reach the finishing line at the same time, it's a mircal\n");
	printf("===================================\n");

	return 0;
}
