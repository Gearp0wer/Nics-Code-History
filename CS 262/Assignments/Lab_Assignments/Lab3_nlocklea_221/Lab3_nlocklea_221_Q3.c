/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 3 Q3
 */

#include<ctype.h>
#include<stdio.h>

enum datatype {JAN, FEB, MAR, APR, MAY, JUN};
int main(){
        int input;
        printf("Please enter an integer: ");
        scanf("%d", &input);
	enum datatype month = input -1;
        switch(month){
                case JAN:
                        printf("This is the first month");
                        break;
                case FEB:
                        printf("This is the second month");
                        break;
                case MAR:
                        printf("This is the third month");
                        break;
                default:
                        printf("This is not one of the first three months");

        }



        return 0;
}
