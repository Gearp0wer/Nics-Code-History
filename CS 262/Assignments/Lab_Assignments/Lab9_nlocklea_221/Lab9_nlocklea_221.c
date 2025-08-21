/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 9 Q1
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

    int arr[2][3];
    int i,j, num=0;
    for (i=0; i<2; i++) {
        for (j=0; j<3; j++) {
             printf("please enter an integer value: ");
             scanf("%d", &num);
             arr[i][j] = num;
        }
    }

    printf("\nlet's print out the element values by indices: \n");
    for (i=0; i<2; i++) {
        for (j=0; j<3; j++) {
            printf("the element stored in row %d and col %d is %d\n", i,j,arr[i][j]);
        }
    }

    //int *ptr = arr[0]; // arr[0]-> arr[0][0]
    int *ptr = &arr[0][0];
    int cnt;
    printf("\nlet's print out the element values by using pointer:\n");
    for (cnt=0; cnt<6; cnt++) {
        printf("the %dth element from the 2D array is: %d\n", cnt, *(ptr+cnt));
    }

    return 0;
}