#include <stdio.h>

	double tspeed; //tortoise speed
	double rspeed;  //rabbit spee
	double rstime; //rabbit stay time
	double length; //runway length

void init()
{
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


}

double rrun(double length)
{
	double t = length / rspeed;
	printf("rabbit run %.21fsecond\n", t);
	printf("rabbit stay%.21fsecond\n", rstime);
	printf("rabbit use%.21fsecond in a total\n", (t + rstime));

	return (t + rstime);
}

double trun(double length)
{
	double t = length /tspeed;
	printf("rabbit run %.21fsecond\n", t);
	
	return t;
}

void start()
{
	printf("\n================================\n");
	printf("game begins!\n");
	printf("come on ...\n");
	printf("rabbit start to have a rest\n");
	printf("rabbit wakes up\n");
	printf("\n================================\n");
	printf("race is over\n");

	double tr = rrun(length);
	double tt = trun(length);

	printf("===================================\n");
	if (tr > tt)
		printf("\nThe game won the tortoise\n");

	else if (tr < tt)
		printf("\nThe game won the rabbit\n");

	else
		printf("\noh my god, tortoise and rabbit reach the finishing line at the same time, it's a mircal\n");
	printf("===================================\n");


}

int main(int argc, const char *argv[])
{
	init();
	start();

	return 0;
}
	
