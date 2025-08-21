/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 6
 * Note: there are newlines inlcuded interittently to help with readability.
 */

#include <stdio.h>
#include <ctype.h>


int main(){
	int user_input[10];
	int threshhold = 50;
	int count = 0; 
	int x = 0;
	printf("Please enter 10 integers: \n");
	for(x = 0; x < 10; x++){
		scanf(" %d", &user_input[x]);
		printf("\n");
		if( user_input[x] > threshhold){
			count +=1;
		}
	}
	printf("There are (%d) entries greater than 50.\n", count);
    	return 0;
}
