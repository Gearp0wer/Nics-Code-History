/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 2 Q2
 */

#include <stdio.h>
#include <ctype.h>

int main(){
    char var;
    printf("Enter a letter: ");
    scanf("%c", &var);

    if(isupper(var))
        printf("%c is an upper letter", var);
    else
        printf("%c is not an upper letter", var);

    return 0;
}
