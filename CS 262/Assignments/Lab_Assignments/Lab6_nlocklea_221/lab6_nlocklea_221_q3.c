/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 6
 *  */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
	int len_str1, len_str2;
	char alpha[20];
	char numeric[20];
	char str3[100];
	char Buffer[15];
	strcpy(alpha, "abcdefgh");
	strcpy(numeric, "123456");
	len_str1 = strlen(alpha);
	len_str2 = strlen(numeric);
	
	if(len_str1 > len_str2){
		strcpy(str3, alpha);
	}
	else{
		strcpy(str3, numeric);
	}
	printf(str3);
	printf(" is the longer string.\n");

	printf("Enter a string less than 15 characters long:\n");
	fgets(Buffer, 15, stdin);
	Buffer[strcspn(Buffer, "\n")] = 0;
	strcat(Buffer, str3);
	printf("\n");
	printf(Buffer);
	printf("\n");


    	return 0;
}
