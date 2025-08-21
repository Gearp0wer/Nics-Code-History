/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 3
 * Note: there are newlines inlcuded interittently to help with readability.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void menu(char *input){
	char Buffer[100]; 
	printf("***********************************************\n");
	printf("Please enter a character: ");
	printf("'i' - insert an item\n'u' - update the database\n's' - search the database\n
	'd' - display the database\n'q' - exit the program\n");
	printf("\n");
	printf("***********************************************\n");
	
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", input);
	printf("\n");
}

void character_select( char *C){
	char Buffer[100];
	printf("Please enter a new character: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", C); 
	printf("\n");
}

void size_select(int *N){
	char Buffer[100]; 
	int myInt = 0; 
	printf("Please enter an odd number between 3 and 15 to determine the size of the design: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%d", &myInt); 
	printf("\n");

	if(myInt < 3 || myInt > 15 ){
		printf("Invalid number.\n");
		size_select(N);
	}
	else if (myInt %2 != 0){
		*N = myInt;
	}
	else{
		printf("Invalid number.\n");
		size_select(N);
	}

}

void plus_output(int N, char C){
	int i;
	int j;

	for(i = 1; i <= N; i++){  
		if(i == ((N / 2) + 1)){  

			for(j = 1; j <= N; j++){  
        			printf("%c", C);
			}  
		}  
		else{  

			for(j = 1; j <= N / 2; j++){
				printf(" ");
			}	
			printf("%c", C);
		}  
		printf("\n");  
	}
	printf("\n"); 
}  

void star_output(int N, char C){
	int m = (2 * N -1);
	int i;
	int j;

	for(i = 1; i <= m; i++){ 

		for(j = 1; j <= m; j++){  
			if(i == j || j == (m - i + 1)){  
				printf("%c", C);  
			}  
			else{  
				printf(" ");  
			}  
		}  
	printf("\n");
	}
	printf("\n");
}


int main(){
	int N = 0;
	char C = ' ';
    	char input;
	menu(&input);

	while ( input != 'q' || input != 'Q'){
		if ( input == 'q' || input == 'Q'){
			break;
		}
		switch(input){
			case 'c':
			case 'C':
				character_select(&C);
				menu(&input);
				break;
			case 'n':
			case 'N':
				size_select(&N);
				menu(&input);
				break;
			case '1':
				plus_output(N, C);
				menu(&input);
				break;
			case '2':
				star_output(N, C);
				menu(&input);
				break;
			default:
				printf("Invalid entry. Returning to menu.\n\n");
				menu(&input);
				break;
		}
	}
	printf("Thank you, goodbye.");
    	return 0;
}

