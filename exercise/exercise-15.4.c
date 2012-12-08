#include <stdio.h>

void main() 
{								/*取16位二进制数据的偶数位，然后输出其构成的10进制数据*/

	unsigned short  a,s=0,b;

	int i,j,n=7,m;

	printf("\ninput an octal number:");		/*输入一个八进制数据*/

	scanf("%o",&a);

	m=1<<15;							/*数据m的最高位为1，其它位为0*/

	for(i=1;i<=8;i++) {

		if (m & a) {					/*得到数据a的最高位，如果最高位为1，那么乘以相应的权值，然后累计相加*/

			for (j=1,b=1;j<=n;j++)

				b*=2;

			s+=b;

		}

		a=a<<2;						/*a左移2位，取偶数位*/

		n--;

	}

	printf("result %d\n",s);

}

