#include <stdio.h>

int main()
{

	int  s[10][10];

	int  i,j,k;

	for(i=0;i<10;i++){					/*为数组中的对角线和第0列元素赋值*/

		s[i][i]=1;s[i][0]=1;

	}

	for(i=2;i<10;i++)					/*为其他的元素赋值*/

		for(j=1;j<i;j++)

			s[i][j]=s[i-1][j-1]+s[i-1][j];

	printf("\n");

	for(i=0;i<10;i++){					/*不输出无意义的元素*/

		for (k=i;k<=10;k++)				/*控制每行的空格*/

			printf("  ");

		for(j=0;j<=i;j++)					/*控制每行的数据*/

			printf("%4d",s[i][j]);

		printf("\n");

	}
	
	return 0;
}

