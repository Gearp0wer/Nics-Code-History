/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 2 Q3
 */

#include <stdio.h>
#include <ctype.h>

int main(){
    char var;
    printf("Enter a character: ");
    scanf("%c", &var);

    if(isalnum(var))
        printf("%c is alphanumeric", var);
    else
        printf("%c is not alphanumeric", var);

    return 0;
}
