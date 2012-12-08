#include <stdio.h>

void main()
{							/*取16位二进制数据每一位，统计其中1的个数。*/

	unsigned short  a;

	int i,c=0;

	printf("\ninput an octal number:");	/*输入一个八进制数据*/

	scanf("%o",&a);

	for(i=1;i<=16;i++) {

		if ( a&1) {					/*得到数据a的最低位，若此位为1，进行统计*/

			c++;

		}

		a=a>>1;					/*a右移1位*/

	}

	printf("\nresult %d\n",c);

}

