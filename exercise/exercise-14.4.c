#include <stdio.h>

#define N 2

#define M 3


int main()
{

	float  score[N][M];				/*存放成绩*/

	float  stu[N],ave[M];				/*存放每个同学的总分，和每一科的成绩总分*/

	float  sort[N][M];				/*存放排序后的结果*/

	float  sum;					/*存放每个学生成绩总和*/

	int i,j,k;

	char ch;

	printf("input score :\n");			/*输入提示*/

	for(i=0;i<N;i++)					/*初始化成绩数组*/

		for (j=0;j<M;j++)

			scanf("%f",&score[i][j]);

	getchar();						/*用getchar输入一个字符*/

	do {							/*输出菜单项*/

		printf("\n\n");

		printf("                              |  input the selected numbers :\n");

		printf("                              |  1.finding\n");

		printf("                              |  2.totle scores\n");

		printf("                              |  3. average of scores:\n");

		printf("                              |  4.exit:\n");

		ch=getchar(); getchar();

		printf("\n");

		switch(ch){				/*判断选择了哪一项*/

			case '1': printf("input the finding numbers:\n");

				  /*查找*/

				  scanf("%d",&i);

				  getchar();

				  for(j=0;j<M;j++)

					  printf("%.2f  ",score[i][j]);

				  /*输出第i个学生*/

				  printf("\n");

				  break;

			case '2':				/*计算总分*/

				  for(i=0;i<N;i++){

					  sum=0;

					  for(j=0;j<M;j++)

						  sum+=score[i][j];

					  stu[i]=sum;

					  printf("the  %d total is %.2f.\n",i,stu[i]);

				  }

				  break;

			case '3':				/*计算平均分*/

				  for(j=0;j<M;j++){

					  sum=0;

					  for(i=0;i<N;i++)

						  sum+=score[i][j];

					  ave[j]=sum/M;

					  printf("the %d subject is %.2f.\n",j,ave[j]);

				  }

				  break;



			default :break;			/*退出*/

		}

		if (ch=='4')  {				/*判断输入字符是否等于‘4’*/

			printf("over !\n");

			break;}				/*结束循环*/

	}while(1);
	
	return 0;
}

