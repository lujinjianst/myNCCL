#include <stdio.h>

struct  date {							/*声明结构体类型*/

	int  year;

	int  month;

	int  day;

};

struct employee {

	int num;

	char  name[20];

	char  sex;

	struct  date   bir;					/*bir为struct date类型*/

	float bwage,bonus,ins,rwage;

};

void main() {

	struct employee worker;				/*定义一个结构体变量worker*/

	printf("input the worker date:\n");		/*输入提示*/

	scanf("%d%s",&worker.num,worker.name);

	getchar();							/*吸收上面输入中多余的回车*/

	worker.sex=getchar();

	scanf("%d%d%d",&worker.bir.year,&worker.bir.month,&worker.bir.day);

	scanf("%f%f%f",&worker.bwage,&worker.bonus,&worker.ins);

									/*输入各成员值*/

	worker.rwage=worker.bwage+worker.bonus-worker.ins;

									/*求出成员的工资*/

	printf(" output:\n ");					/*输出提示*/

	printf("\n	num      name	   real wage\n");

	printf("	%d	 %5s	   %.2f\n",worker.num,worker.name,worker.rwage);

}
