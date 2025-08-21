/*
 *Nicholas Locklear
 *G01090642
 *Lab 8 q3
 *CS 262 - 221
 */

#include <stdio.h>
#define MAX_SIZE 100

int main(){
    char str1[MAX_SIZE], str2[MAX_SIZE];
    char * s1 = str1;
    char * s2 = str2;

    printf("Enter first string: ");
    fgets(str1, 10, stdin);
    printf("Enter second string: ");
    fgets(str2, 10, stdin);
    str1[strcspn(str1, "\n")] = '\0';

    while(*(++s1));

    while(*(s1++) = *(s2++));


    printf("Concatenated string = %s", str1);

    return 0;
}