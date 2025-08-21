/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 6
 * Note: there are newlines inlcuded interittently to help with readability.
 */

#include <stdio.h>
#include <ctype.h>


void multiplier(int *user_input, int size){
	int x;
	for(x = 0; x < size; x++){
		printf("%d\n", user_input[x] *2);
	}

}

int main(){
	int user_input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	multiplier(user_input, 10);
    	return 0;
}
