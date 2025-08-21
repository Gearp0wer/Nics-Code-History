/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 5 Q3
 */


#include <stdio.h>
#include <ctype.h>

unsigned long long factorial(int input){
	
	if( input == 0){
		return 1;
	}
	else{
		return (input * factorial( input -1));
	}
}

int main(){

	unsigned long long factor = 0;
	printf("Enter an integer: \n");
	scanf("%llu", &factor);

	factor = factorial(factor);
	printf("factorial of input is: %llu\n", factor);

	return 0;
}