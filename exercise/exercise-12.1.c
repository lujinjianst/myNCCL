#include <stdio.h>

int main()
{

	int i;

	char str[80];				/*定义一个字符串数组str*/

	for(i=0;i<80;i++) 
	{

		str[i]=getchar();			/*逐次给数组元素str[i]赋值*/

		printf("*");				/*以星号代替输入字符的个数*/

		if(str[i]=='\n')

			break;			/*若输入回车则终止循环*/

	}

	i=0;

	while(str[i]!='\n')

		printf("%c",str[i++]);		/*逐次输出字符数组的各个元素*/

	printf("\n");

	return 0;
}
