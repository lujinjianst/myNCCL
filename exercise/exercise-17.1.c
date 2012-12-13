#include <stdio.h>

/* 函数的功能是实现字符串的匹配，字符串t中含有通配符*/

int pattern (char *s,char *t) {

	char *ps,*pt,*p;

	ps=s;

	while (*ps ) {						/*逐个字符处理字符串s */

		pt=t;p=ps; 					/* 利用p保存当前比较位置*/

		while (*pt && *pt=='?' || *pt==*ps) 	/* s中逐个字符与字符串t进行比较*/

			pt++,ps++; 				/*通配符或者两个位置字符相等，字符指针后移*/

		if (*pt=='\0') 					/* 找到子串位置*/

			return p-s;

		ps=p+1;

	}

	if (*pt=='\0' && *ps=='\0') { 				/*外循环退出后判断是否有匹配成立*/

		return p-s;

		return -1;

	}
}

void main() {

		char s[50],t[20];

		int i;

		printf("input string s and t:\n");

		gets(s);gets(t);

		i=pattern(s,t);

		if(i!=-1) 

			printf("find,the position %d.\n",i);

		else

			printf("don't find.\n");

	}


