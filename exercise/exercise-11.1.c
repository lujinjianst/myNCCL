#include <stdio.h>

typedef int int32_t;

typedef struct student{
	int id;
	float score;
}stu_info;

int main(void)
{
	int a = 10;
	int32_t b = 21;
	stu_info stu;
	struct student stu_info;

	printf("int a:%d\n", a);
	printf("int32_t b:%d\n", b);

	stu_info.id = 1;
	stu_info.score = 3.24;

	printf("stu_info.id:%d\n", stu_info.id);
	printf("stu_info.score:%f\n", stu_info.score);

	stu.id = 1;
	stu.score = 3.24;
	printf("stu.id:%d\n", stu.id);
	printf("stu.score:%f\n", stu.score);
	return 0;
}
