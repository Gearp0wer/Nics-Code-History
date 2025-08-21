/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 2
 */

#include<ctype.h>
#include<stdio.h>
#include <math.h>

int main(){

/* Constant and variable declaration */
	#define CONST_ONE 0.007184
	#define CONST_TWO 0.425
	#define CONST_THREE 0.725
	float height;
	float weight;
	double BSA;

/* the scanner to read input and calc BSA */
	printf("Please enter a weight in Kg: ");
	scanf("%f", &weight);
	printf("Please enter a height in cm: ");
	scanf("%f", &height);
	BSA = (CONST_ONE * (pow(weight, CONST_TWO)) * (pow(height, CONST_THREE)));

/* output statements */	
	printf("The Height is: %.1f cms\n", height);
	printf("The Weight is: %.1f kgs\n", weight);
	printf("BSA: %.4f meter square\n", BSA);

	return 0;
}
