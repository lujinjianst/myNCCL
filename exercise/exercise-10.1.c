#include <stdio.h>

int f(int a,int b,int c) {			/*定义f函数*/

	int z;

	z=a+b*c;

	return z;				/*返回一个整型值*/

}

int main(){

	int x=3,y;

	y=f(x,x++,x++);			/*由右至左对实参求值*/

	printf("%d\n",y);

	return 0;

}

