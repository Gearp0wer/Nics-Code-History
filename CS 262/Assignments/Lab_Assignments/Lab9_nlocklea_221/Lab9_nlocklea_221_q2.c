/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 9 Q2
 * 
 */

#include <stdio.h>
#include <stdlib.h>

const int size=10;

void subFnc(int *);

int main() {
   int *num = (int *)malloc(size * sizeof(int));
   int i;
   for (i=0;i<size;i++) {
       printf("please input the %dth integer value: ", i);
       scanf("%d", (num+i));
   }

   subFnc(num);
   free(num);
   return 0;
}

void subFnc(int *num) {
     int cnt = 0;
     while (cnt < size) {
         printf("the %dth element stored in the memory is %d.\n", cnt, *(num+cnt));
         cnt += 1;
     }
}