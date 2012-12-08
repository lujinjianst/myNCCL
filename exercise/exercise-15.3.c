#include <stdio.h>

void main() 
{ 

	unsigned short int a,b=1;

	printf("input an octal number:");

	scanf("%o",&a);

	b=a&0100000;				/*数据0100000的二进制数据的最高位为1,其余为0*/

	if (b==0100000)				/*如果a小于0*/

		a=~a+1;					/*按位取反,末位加1*/

	printf("result:%o\n",a);

}

