/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 2 Q1
 */

#include <stdio.h>

int main(){
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    if(num%5==0 && num%7==0)
        printf("%d is the multiple", num);
    else
        printf("%d is not the multiple", num);
    return 0;
}
