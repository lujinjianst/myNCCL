#include "stdio.h"

float average(float *p,int n){			/*形参为指针变量*/

	float *p_end,sum=0,aver;

	for(p_end=p+n-1;p<=p_end;p++)

		sum=sum+(*p);				/*一维数组的形式访问全部的数据*/

	aver=sum/n;					/*求平均值*/

	return aver;

}

void output (float (*p)[4],int  n) {		/*形参为指向数组的指针*/

	int k,i,j;

	for (i=0;i<n;i++,p++) {			/*i用来控制数组的行*/

		k=0;

		for (j=0;j<4;j++)

			if (*((*p)+j)<60)  k++;	/*统计不及格的人数*/

		if (k>2)

			printf("No. %d is fail,his score are:\n",i+1);

		for(j=0;j<4;j++)				/*j用来控制数组的列*/

			printf("%4.2f",*((*p)+j));

	}

}

main()
{

	float score[3][4]={65,99,70,60,80,87,90,81,90,67,97,98};

	/*定义一个二维数组score*/

	float av;

	av=average(*score,12);			/*实参是一个一维数组名*/

	printf("average:%4.1f\n",av);

	output(score,3);				/*实参是一个二维数组名*/

	printf("\n");

}

