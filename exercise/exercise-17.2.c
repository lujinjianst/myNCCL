#include <stdio.h>
#include <string.h>

/* 函数的功能是利用字符串v替换字符串s中出现的子串t*/

void replace (char *s,char *t,char *v) {

	char *ps=s,*pt,*p=ps;

	char temp[40]; 				/* 设置辅助数组*/

	int n;

	while (*ps) { 				/* 逐个字符扫描字符串s*/

		pt=t; 

		while (*ps && *pt){ 		/* 寻找字符串t在s中的位置*/

			if (*ps==*pt) {		/*对应字符相同*/

				ps++;

				pt++;

			}

			else {

				ps=p+1;

				p=ps;

				pt=t;

			}

		}

		if (*pt=='\0'){  			/*如果找到字符串t在s中位置进行字符串替换*/

			strcpy(temp,ps);	/* 保存字符串s中t字符串后的其他字符*/

			*p='\0'; 			/* 字符串s缩小*/

			strcat(s,v); 		/* 字符串s和v连接*/

			n=strlen(s);

			ps=s+n;

			strcat(s,temp); 		/* 连接字符串s和temp*/

		}

	}

}

void main() {

	char s[40],t[10],v[10];

	printf("input string s,t,v:");

	gets(s),gets(t),gets(v);

	replace(s,t,v);

	printf("output the string %s\n",s);

}

