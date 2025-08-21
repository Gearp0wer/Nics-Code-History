/*
 * Nicholas Locklear
 * G01090642
 * Cs 262 Section 211
 * Lab 7
 */

#include <stdio.h>
#include <ctype.h>


int main(){
	int* p1, N = 100;
	p1 = &N;
	printf("%d\n", p1);
	printf("%d\n", *p1);
	printf("%d\n", ++p1);

	p1 = &N;
	printf("%d\n", ++(*p1));
	printf("%d\n", *(p1++));
	return 0;

}
