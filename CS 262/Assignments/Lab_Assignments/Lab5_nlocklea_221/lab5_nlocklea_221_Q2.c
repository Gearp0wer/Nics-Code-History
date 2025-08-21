/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 5 Q2
 */

#include <stdio.h>

void func1();
int a, b = 10;

void func1(){
	int a = 1;
	static int b = 100;
	printf("a = %d\n", a);
	printf("b = %d\n\n", b);
	a++;
	b++;
}

int main (){
	printf("a, b: %d, %d\n", a, b);
	func1();
	func1();
	func1();
	printf("New a, b: %d, %d\n", a, b);
	return 0;
}
