#include <stdio.h>

int main(void)
{ 

	int a,b=31,c;

	printf("input an octal  data :");			/*输入提示*/

	scanf("%o",&a); 					/*八进制形式输入一个数据*/

	c=a|b;							/*按位与运算保存数据的低五位*/

	printf("a=%o\tb=%o\tc=%o\n",a,b,c);

}

