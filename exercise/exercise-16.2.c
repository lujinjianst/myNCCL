#include <stdio.h>

int max(int x,int y) {					/*函数的功能是两个数的最大值*/

	return (x>y?x:y);

}

int add(int x,int y) {					/*函数的功能是求两个数的和*/

	return (x+y);

}

int sub(int x,int y) {					/*函数的功能是求两个数的差*/

	return (x-y);

}

void operate(int x,int y,int (*fun)() ) {

	printf("%d\n",(*fun)(x,y));			/*取得函数入口*/

}

main(){

	int a,b;						/*定义两个整型变量*/

	scanf("%d%d",&a,&b);			/*输入两个数*/

	printf("Max=");

	operate(a,b,max);				/*函数名作实参*/

	printf("Add=");

	operate(a,b,add);

	printf("Sub=");

	operate(a,b,sub);

}

