/*
 *Nicholas Locklear
 *G01090642
 *Lab 8 q2
 *CS 262 - 221
 */

#include <stdio.h>

void add(int a,int b){
	printf("%d\n", a+b);
}
void subtract(int a, int b){
	printf("%d\n", a-b);
}
void multiply(int a, int b){
	printf("%d\n", a*b);
}
void divide(int a, int b){
	printf("%d\n", a/b);
}

void calulator(void (*func)(int, int)) {
	func(20,10);
}

int main() {
    calulator(add);
    calulator(subtract);
    calulator(multiply);
    calulator(divide);
    return 0;
}