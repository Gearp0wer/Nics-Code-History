/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 4
 */

#include <stdio.h>

int sum(int num1, int num2){
	int result;
	result = num1 + num2;
	return result;
}

int main(){
	int a = 6;
	int b = 5;	
	int ret;

	ret = sum(a,b);
	printf("Sum is: %d\n", ret);
	return 0;
}