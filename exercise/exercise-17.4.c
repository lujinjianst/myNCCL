#include <stdio.h>
#include <stdlib.h>
/*将字符串s1拆分成字符串s2和字符串s3，要求字符串s2是长n且两端对齐*/

void format(char *s1,char *s2,char *s3,int n) {

	char *p=s1,*q=s2;

	int i=0;

	while (*p &&*p==' ') p++;				/*滤掉s1左端空格*/

	if (*p=='\0') {

		printf("string is blank.\n");

		exit(0);

	}

	while(*p && i<n) {					/*字符串s1向字符串s2中复制*/

		*q=*p;q++;

		p++;i++;

	}

	if (*p=='\0') {						/*未找到*/

		printf("string don't have %d character.\n",n);

		exit(0);

	}

	if (*(--q)==' ') { 				/*若最后一个字符为空格，则需向后找到第一个非空格字符*/

		p--;

		while (*p==' ' && *p) p++;			/*往后查找一个非空格字符作串s2的尾字符*/

		if (*p=='\0'){

			printf("string don't have %d left-right character.\n",n);

			exit(0);

		} 

		*q=*p;         				/*字符串s2最后一个非空字符*/

		*(++q)='\0';   

	}

	q=s3;p++;							/*将s1串其余部分送字符串s3 */

	while (*p!= '\0') { 

		*q=*p; q++; p++;

	}

	*q='\0';        					/*置串s3结束标记*/

}

void main() { 

	char s1[40],s2[30],s3[30];

	int n;

	printf("input string s1:\n");

	gets(s1);

	printf("input data n:\n");

	scanf("%d",&n);

	format(s1,s2,s3,n);

	printf("string s2 and s3:\n");

	puts(s2);

	puts(s3);

}

