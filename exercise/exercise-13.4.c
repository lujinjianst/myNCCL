#include <stdlib.h>

#include <string.h>

struct card {							/*定义结构体类型*/

	int num;

	char kind;

};

struct card deck[52];						/*定义结构体数组*/

void swap(struct card *,struct card *);		/*声明函数swap*/

void moni(struct card d[] )
{					/*模拟人工洗牌过程*/

	int i,j;

	random();

	for(i=0;i<52;i++) {

		j=rand()%52;

		swap(&d[i],&d[j]);

	}

}

void swap(struct card *p1,struct card *p2)
{	/*交换结构体指针所指变量*/

	struct card temp;					/*定义结构体变量*/

	temp=*p1;	

	*p1=*p2;

	*p2=temp;

}

int main()
{

	int i;

	for (i=1;i<=52;i++) {

		switch (i/13) {					/*多分支选择结构*/

			case 0:

				deck[i].num=i%13;

				deck[i].kind='C'; 		/*随机到梅花*/

				break;

			case 1:

				deck[i].num=i%13;

				deck[i].kind='D'; 		/*随机到方块*/

				break;

			case 2:

				deck[i].num=i%13;

				deck[i].kind='H'; 		/*随机到红心*/

				break;

			case 3:

				deck[i].num=i%13;

				deck[i].kind='S'; 		/*随机到黑心*/

				break;

		}

	}

	deck[13].num=13,deck[26].num=13;

	deck[39].num=13,deck[52].num=13;

	moni(deck);						/*函数调用，结构体数组名作实参*/

	for (i=0;i<52;i++)

		if (i%13 ==0)					/*判断i是否除13余数为0*/

			printf("\nNo. %d:",i/13+1);

		else

			printf("%c%2d ",deck[i].kind,deck[i].num);
	printf("\n");

	return 0;

}

