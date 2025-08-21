/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 6
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * Function purposes in order:
 * isNumber: check if the command line args are integers
 * InputValidation: Only used if the above returns 0, standard input validation
 * Comparator: A comparison function for qsort
 * ArrayPrinter: outputs the permutations
 * randPerm: randomly sorts the array into a permutation
 * Initialize Array: does as name suggests
 * Main: this is where everything else gets handled, including welcome message, allocation, looping, etc
 */

int isNumber(char number[]){
	int i = 0;
	if (number[0] == '-'){
		i = 1;
	}
	for(i=i; i < strlen(number); i++){
        	if(!isdigit(number[i])){
			return 0;
		}
    	}
    return 1;
}

void InputValidation(int *Seed, int *Size){
	char Buffer[100];
	char newseed = ' ';
	char newsize = ' ';
	printf("Enter the Seed: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", &newseed);
	printf("\n");
	printf("Enter the size: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", &newsize);
	printf("\n");
	if(isdigit(newseed) == 0 || isdigit(newsize) == 0 ){
		printf("Invalid input detected. Please try again.\n");
	 	InputValidation(Seed, Size);
	}
	else if(newsize - '0' <= 0){
		printf("Invalid input detected. Array cannot have a negative size. Please try again.\n");
	 	InputValidation(Seed, Size);
	}
	else{
		*Seed = newseed - '0';
		*Size = newsize - '0';
	}
}

int Comparator(const void * a, const void * b){
	return (*(int*)b - *(int*)a);
}

void ArrayPrinter(int *numArray, const int arrayLength){
	int i;
	for(i = 0; i < arrayLength; i++){
		printf("%d ", numArray[i]);
	}
	printf("\n");
}

void randperm(int *numArray, const int n){
	int i, j;
	int Placehold;
	for(i = n - 1; i > 0; i--){
		j = rand()%(i + 1);
		Placehold = numArray[j];
		numArray[j] = numArray[i];
		numArray[i] = Placehold;
	}
	ArrayPrinter(numArray, n);
}

void InitializeArray(int *numArray, const int arrayLength){
	int i;
	for(i = 0; i < arrayLength; i++){
		numArray[i] = i;
	}
	ArrayPrinter(numArray, arrayLength);
}

int main(int argc, char *argv[]){
	int Seed = atoi(argv[1]);
	int Size = atoi(argv[2]); 
	int i;
	int *numArray = malloc(sizeof(int) * Size);
	printf("\n\nWelcome!\nThis is Nicholas Locklear's Permutation Generator.\nID: G01090642, Lab Section: 221\n\n");
	if(isNumber(argv[1]) == 0 || isNumber(argv[2]) == 0){
		printf("Either input [%s] or [%s] is invalid.\n", argv[1], argv[2]);
	 	InputValidation(&Seed, &Size);
	}
	srandom(Seed);
	if (numArray == NULL){
        	printf("Error allocating memory. Exiting Program.");
	free(numArray);
        exit(1);
	}
	for(i = 0; i < 10; i++){
		InitializeArray(numArray, Size);
		randperm(numArray, Size);
		qsort(numArray, Size, sizeof(int), Comparator);
		ArrayPrinter(numArray, Size);
		printf("\n");
	}
	free(numArray);
	return 0;
}