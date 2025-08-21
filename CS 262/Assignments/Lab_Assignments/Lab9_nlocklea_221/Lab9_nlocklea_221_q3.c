/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 9 Q3
 * 
 */

#include <stdio.h>
#include <stdlib.h>

const int size=10;
void subFnc(int *);
void subFnc2(int *);

int main(){
   int *num = (int *)malloc(size * sizeof(int));
   int i;

   for (i=0;i<size;i++){
       printf("Enter the %dth integer value: ", i);
       scanf("%d", (num+i));
   }
   subFnc(num);
   subFnc2(num);
   free(num);
   return 0;
}

void subFnc(int *num){
     int cnt = 0;
     printf("\n\nThe stored array in the memory\n", *(num+cnt));

     while (cnt < size){
         printf("%d ", *(num+cnt));
         cnt += 1;
     }
}

void subFnc2(int *num){
    int i;
    printf("\nIncreasing the size of the array by 5 elements ...\n ");
    num = (int*)realloc(num, 15 * sizeof(int));
    printf("\nEnter 5 more integers\n\n");

    for(i = 10; i < 15; i++){
        printf("Enter the %dth integer value: ", i);
        scanf("%d", num+i);
    }
    printf("\nNew array: \n\n");

    for(i = 0; i <15; i++){
        printf("%d ", *(num+i) );
    }

}