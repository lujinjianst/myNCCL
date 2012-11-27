#include <stdio.h>

float  f(float  x) 
{

	float y;

	y=1/(1+x*x);

	return y;

}

float jifen(float a,float b)
{

	int i,j,n;

	float x,h,s;

	printf("please input  n:");

	scanf("%d",&n);

	h=(b-a)/n;						/*计算出梯形的高h*/

	s=(f(a)+f(b))/2;					/*调用函数f求出梯形面积的初值*/

	for( i=1;i<n;i++){

		x=a+i*h;

		s=s+f(x);

	}

	return s*h;

}



int main()
{

	float a,b,s;

	printf("input range between a and b :");

	scanf("%f%f",&a,&b);				/*输入积分的区间*/

	s=jifen(a,b);						/*调用函数jifen*/

	printf("the  value is :%f\n",s);

	return 0;
}


