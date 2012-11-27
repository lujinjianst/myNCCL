#include  <stdio.h>


#define  MIN    6		/*密码最小长度*/

#define  MAX  12		/*密码最大长度*/

int main()
{

	int loop;

	char password[13];	/*为密码字符串预留1个结束标志位*/

	printf("\n Please input the password (6~12 characters): ");

	for( loop = 0; loop < MAX; loop++){

		password[loop] = getchar();

		printf("*");			/*以星号代替密码字符显示*/

		if(password[loop]=='\x0d')	/*回车，结束密码输入*/

		{ if( loop < MIN ) 	/*长度<6，提示重输*/

			{ printf("\n The length of the password is less than 6,press any key to continue...");

				getchar();		/*暂停，按任意键继续*/

				printf("\n Please input the password again (6~12 characters): ");

				loop = -1;	/*执行“loop++”后，使下标复位为0*/

			}

			else	{		    /*密码长度在6~11之间*/

				password[loop] = '\0';    /*置密码串结束标志*/

				break;

			}

		}

		if( loop == MAX -1)	/*密码长度达到最大值MAX*/

			password[loop] = '\0';	/*置密码串结束标志*/

	}
	
	return 0;
}
