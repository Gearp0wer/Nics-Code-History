/*
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 3 Q2
 */

#include <stdio.h>
#include <ctype.h>

int main(){
	int var;
	int initial;
	int sum;
	printf("Enter an integer: ");
	scanf("%d", &var);	
	
	/* do loop execution */
   	LOOP:do {
   
      		if( initial %3 ==0) {
         		/* skip the iteration */
         		sum = sum + initial;
			initial++;
         		goto LOOP;
      		}
		if( initial %5 ==0) {
	         	/* skip the iteration */
	         	sum = sum + initial;
			initial++;
			
	         	goto LOOP;
		}

		
      	initial++;

   	}while( initial <= var );
	printf("Sum = %d", sum); 
   	return 0;

}
