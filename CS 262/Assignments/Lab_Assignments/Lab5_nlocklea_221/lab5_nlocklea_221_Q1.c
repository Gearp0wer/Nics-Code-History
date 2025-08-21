/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 5 Q1
 */

#include <stdio.h>
#include <ctype.h>

void 
shift(char *a, char *b, char *c, char *d){
	*a += 4;
	*b += 4;
	*c += 4;
	*d += 4;
}

int main(){

	char a, b, c, d;
	printf("Enter 4 characters: \n");
	scanf(" %c %c %c %c", &a, &b, &c, &d);
	shift(&a, &b, &c, &d);
	printf("shifted variables are: %c %c %c %c", a, b, c, d);
	

	return 0;
}
