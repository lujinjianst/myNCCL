#include <stdio.h>

int  main (void)
 {
   int value = 0xFF;

   printf("The inverse of %X is %X\n", value, ~value);

   printf("\n");
   printf("0 & 0 is %d\n", 0 & 0);
   printf("0 & 1 is %d\n", 0 & 1);
   printf("1 & 1 is %d\n", 1 & 1);
   printf("1 & 2 is %d\n", 1 & 2);
   printf("15 & 127 is %d\n", 15 & 127);


   printf("\n");
   printf("0 | 0 is %d\n", 0 | 0);
   printf("0 | 1 is %d\n", 0 | 1);
   printf("1 | 1 is %d\n", 1 | 1);
   printf("1 | 2 is %d\n", 1 | 2);
   printf("128 | 127 is %d\n", 128 | 127);

   printf("\n");
   printf("0 ^ 0 is %d\n", 0 ^ 0);
   printf("0 ^ 1 is %d\n", 0 ^ 1);
   printf("1 ^ 1 is %d\n", 1 ^ 1);
   printf("1 ^ 2 is %d\n", 1 ^ 2);
   printf("15 ^ 127 is %d\n", 15 ^ 127);

   return 0;
 }
