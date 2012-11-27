#include <stdio.h>

int  index (char s[],char t[])
{							/*定义函数*/

	int i,j,k;

	for (i=0;s[i];i++){								/*s[i]不为\0*/

		for (j=i,k=0;t[k] && s[j]==t[k];j++,k++) ;			/*j和k同步移动*/

		if (t[k]=='\0') 								/*存在匹配关系*/

			return i;

	}

	return -1;

}

int main() 
{

	char s1[80],s2[20];								/*定义两个字符数组*/

	int k;

	printf("input string s1 and s2:\n");					/*输入提示*/

	gets(s1);gets(s2);

	k=index(s1,s2);									/*判断是否匹配*/

	if (k==-1)

		printf("%s is not  in %s",s2,s1);

	else

		printf("%s is in %s ,the first position %d",s2,s1,k);
	
	return 0;
}

