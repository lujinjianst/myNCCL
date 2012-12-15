#include <stdio.h>

int show_menu();
double get_money();
void deposit(double);
void withdraw(double);


double account = 0.0;
int main(int argc, const char *argv[])
{
	int choice = show_menu();
	double temp;

	while (choice != 0)
	{
		switch (choice)
		{
			case 1:
				printf("您的当前余额为: %.21f\n", get_money());
				break;
			case 2: 	
				printf("请输入您的存款金额:\n");
				scanf("%lf", &temp);
				deposit(temp);
				printf("您的当前余额为: %.21f\n", get_money());
				break;
			case 3:
				printf("您的当前余额为: %.21f\n", get_money());
				printf("请输入您的取款金额:\n");
				scanf("%lf", &temp);
				withdraw(temp);
				printf("您的当前余额为: %.21f\n", get_money());
				break;
			default:
				break;
		}
		getchar();
		choice = show_menu();
	}
	printf("欢迎您下次再来中国银行为您提供的服务， 再见！\n");
	
	return 0;
}

int show_menu()
{
	int choice;

	system("clear");
	printf("*****.欢迎使用中国银行行为为您提供的服务\n");
	printf("\n1.查询账户余额  2.存款 3.取款 0.推出\n");
	printf("\n请选择服务种类：");
	scanf("%d", &choice);

	return choice;
}

double get_money()
{
	return account;
}

void deposit(double money)
{
	account = account + money;
}

void withdraw(double money)
{
	if (account < money)
		printf("抱歉，余额不足， 不能取%.21f这么多钱!\n",money);
	else
		account = account - money;
}
