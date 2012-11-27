#include <stdio.h>

struct employee {									/*定义一个结构体类型*/

	int num;

	char name[20];

	float bwage,bonus,tax,ins,rwage;

};

float realwage(struct employee w) {						/*定义函数realwage*/

	w.tax=(w.bwage+w.bonus)*0.05;

	w.rwage=w.bwage+w.bonus-w.tax-w.ins;

	return w.rwage;/*返回实发工资*/

}

int main() 
{

	struct employee w1={115,"dongfang",1500,500,0,10,0};	/*结构体变量w1初始化*/

	w1.rwage=realwage(w1);

	printf("name %s real wage  %.2f\n",w1.name,w1.rwage);/*输出成员的姓名和实发工资*/

	return 0;
}/*调用函数*/

