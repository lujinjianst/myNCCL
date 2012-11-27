#include <stdio.h>

#define MAX  15			/*宏定义*/

int main()
{

	int magic [MAX][MAX];

	int cur_i=0,cur_j;		/*填充数据的下标*/

	int count,n ,i,j;

	do{

		/*输入阶数，只接受奇数*/

		printf("\n enter squqre n(ODD) number:");

		scanf("%d",&n);

	}while((n%2)==0);

	cur_j = (n-1) / 2;

	for(count=1;count <=n*n;count++){

		magic[cur_i][cur_j] = count;

		/*第一个元素放在正中*/

		if ((count % n == 0)){

			/*最近的插入的元素为n的整数倍，下面一行，同列为新的位置*/

			cur_i = cur_i+1; 

			continue;

		}

		cur_i = cur_i-1;

		cur_j = cur_j + 1;

		/*下一个到右上角*/

		if (cur_i == -1)

			/*如果行越界*/

			cur_i += n;

		else if(cur_j>n-1)

			/*如果列越界*/

			cur_j -= n;

	}

	for (i = 0;i < n;i++){		/*输出魔方阵*/

		printf("\n");

		for (j = 0;j <n;j++)

			printf("%3d",magic[i][j]);

	}
	printf("\n");

	return 0;
}

