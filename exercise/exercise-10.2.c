#include <stdio.h>

#define N 10

void fun(int a[][N],int n)
{

	int i,j, m=1;

	for (i=0;i<=n/2;i++){

		for (j=i;j<n-i;j++)			/*从左向右*/

			a[i][j]=m++; 

		for (j=i+1;j<n-i;j++)			/*从上向下*/

			a[j][n-1-i]=m++;

		for (j=n-2-i;j>=i;j--)			/*从右向左*/

			a[n-1-i][j]=m++;

		for (j=n-2-i;j>=i+1;j--)			/*从下向上*/

			a[j][i]=m++;

	}

}

int main()
{

	int i,j,n,a[N][N];					/*定义一个二维数组*/

	printf("Enter n:");

	scanf("%d",&n);					/*输入数据n*/

	fun(a,n);						/*调用函数*/

	for (i=0;i<n;i++){

		for (j=0;j<n;j++)

			printf("%4d ",a[i][j]);		/*输出数组a元素*/

		printf("\n");

	}
	
	return 0;
}

