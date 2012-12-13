#include <stdio.h>

main(){

  char str1[50],str2[50],*p1,*p2;

  int num=0;

  printf("please input two strings\n");

  gets(str1);

  gets(str2);

  p1=str1;p2=str2;

  while(*p1!='\0') {					/*未到结尾*/
  
      if(*p1==*p2) {
      
            while(*p1==*p2&&*p2!='\0') {  	/*判断str1是否包含和str2相等的子串*/
	    
	             p1++;					/*指针后移*/
	    
	             p2++;    }
      
          }
  
      else
  
        p1++;
  
      if(*p2=='\0')    num++;			/*存在子串*/
  
      p2=str2;
  
      }

  printf("%d\n",num);

}

