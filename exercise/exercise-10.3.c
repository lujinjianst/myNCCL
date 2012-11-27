#include <stdio.h>

void trangle(int n)
{				/*定义类型为void的函数trangle*/

	int i,j;

	for (i=0;i<n;i++){			/*控制行*/
	
			for (j=0;j<=n-i;j++)		/*控制每行输出的空格数*/
	
				putchar(' ');
	
			for (j=0;j<=2*i;j++)		/*控制每行输出的‘*’数*/
	
				putchar('*');
	
			putchar('\n');
	
		}

}

int main()
{

	int n;

	printf("Enter n: ");

	scanf("%d",&n);				/*输入数据n*/

	printf("\n");

	trangle(n);					/*函数调用*/
	
	return 0;
}

