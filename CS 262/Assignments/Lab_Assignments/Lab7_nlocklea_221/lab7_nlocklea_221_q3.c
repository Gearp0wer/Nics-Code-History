/*
 * Nicholas Locklear
 * G01090642
 * Cs 262 Section 211
 * Lab 7
 */

#include <stdio.h>
#include <ctype.h>



int main(){
	int v1 = 1,v2 = 2,v3 = 3;

	const int  *cP1 = &v1;
	int* const cP2 = &v2;
	const int *const cP3 = &v3;

	const_pointer1 = &v2;

	printf("v1 : %d\n", *const_pointer1);
	printf("v2 : %d\n", ++(*const_pointer2));
	printf("v3 : %d\n", *const_pointer3);
	printf("v3 cannot change its value");
	return 0;
}