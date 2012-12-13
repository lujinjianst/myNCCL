#include <stdio.h>

void maxstr( char s[],char t[]) {

	int i,j,k,len1,con;

	int index=0,len=0;

	i=0;

	while (s[i]) {

		j=0;

		if (s[i]==t[j] && t[j]) { 										/*元素相同*/

			k=1;len1=1;con=1;

			while (con)

				if (  s[i+k]==t[j+k]  && s[i+k] && t[j+k]){

					len1++,k++;

				}

				else   con=0;								/*出现不连续*/

			if (len1>len) { 									/*新的最大长度*/

				index=i;

				len=len1;

			}										/*保留当前长度和下标*/

			i+=k;

		}

		else   j++  ;										/*查找下一个*/

		i++;

	}

	printf("the max consub position is %d,length is %d",index,len);

}

void main() {

	char s[80],t[20];

	printf("input string s ans t:\n");

	gets(s);

	gets(t);

	maxstr(s,t);

	printf("\n");

}
