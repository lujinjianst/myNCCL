#include <stdio.h>

int  main(void)
{
	int button;										/*定义整型变量*/

	printf("==========Beverages ==========\n");		/*输出普通字符串*/

	printf("1.coco-cola\n");

	printf("2.sprite\n");

	printf("3.orangeade\n");

	printf("4.black tea\n");

	printf("5.water\n");

	printf("press 1 to 5 to select:\n");					/*输入提示*/

	scanf("%d",&button);								/*输入数据*/

	switch(button)
	{									/*根据种类输出信息*/

		case 1:printf("\n you buy a bottle of coco-cola. \n");break;

		case 2:printf("\n you buy a bottle of sprite.\n");break;

		case 3:printf("\n you buy a bottle of orangeade.\n");break;

		case 4:printf("\n you buy a bottle of black tea.\n");break;

		case 5:printf("\n you buy a bottle of water.  \n");break;

		default:printf("\n Error !\n");break;				/*其他情况*/

	}

	return 0;
}
