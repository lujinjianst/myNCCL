#include <stdio.h>

#include <string.h>

void strcpy_space(char s[],int n){

	int i=0;

	char t[40];

	while (i<n)

		t[i++]=' ';						/*空格存入数组*/

	t[i]='\0';							/*字符串结束*/

	strcat(s,t);

}

main()

{ char s1[40];

	printf("Enter string s1:");

	gets(s1);

	printf("the string %s,",s1);

	printf("over.\n");

	strcpy_space(s1,5);					/*调用自定义函数*/

	printf("the string %s,",s1);

	printf("over.\n");

}

