/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 8
 * Ascii to Binary converter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ascToBinary(int character, int *ones){
	if(character == 1){
		printf("1");
		*ones+=1;
		return;
        }
        else{
		char out;
		if((character%2) == 0){
			out = '0';
			character = character/2;
		}
		else{
			out = '1';
			character = character/2;
			*ones+=1;

		}
		ascToBinary(character, ones);
		putchar (out);
	}
}

int main(){
	int* ones = [
	ascToBinary
	return 0;
}
