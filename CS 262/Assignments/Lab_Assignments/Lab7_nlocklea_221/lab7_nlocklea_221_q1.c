/*
 * Nicholas Locklear
 * G01090642
 * Cs 262 Section 211
 * Lab 7
 */

#include <stdio.h>
#include <ctype.h>


void switch(int *A, int *ch){
	int temp = *A;
	*A = *ch;
	*ch = temp;
}


int main(){
	int A = 10;
	int ch = 30;

	int *p1 = &A;
	int *p2 = &ch;

	switch(p1, ch);
	

	printf("p1: %f, p2: %f\n", p1, p2);
	printf("p1: %f, p2: %f\n", *p1, *p2);

	return 0;	
}