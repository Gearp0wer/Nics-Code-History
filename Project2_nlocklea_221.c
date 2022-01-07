/* 
 * Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Project 2
 * 
 Current Objectives
	code thse options
		1) Read in the name of a text file to use as a cipher key [DONE]
		2) Create a cipher using the input text file (and save the result to a file) [IN PROGRESS]
			max: 1500 char (including the carriage return and NULL terminator)
			Plan: 
				write sub functions to search through input and return first index of a match
				if no match found, replace with "#"
				then, append them as characters to a 2d coordinate array, in the format "("X,Y")("#,#"), where every char has an associated substring, including whitespace"
				prompt user for filenmame, go through verification, then write array to file as a string
			I have not been able to get the randomized part working very well, I cannot get it to loop back over the list if a character match was found, but the nth instance 
				hadnt been reached before the EOF :(
		3) Decode an existing cipher (prompt user for a file to read containing the cipher text) [DONE]
			invert of cipher (sorta)
			to get index, mult. current num by 10 and add next int from string if available
		4) Exit the program and free all [DONE]

This is long, messy, and held together with glue and duct tape. I'm not particularly proud of it, but it DOES work and I'll settle for that. Functions do as named(mostly)
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int stringlen(char Input[]){
	int c = 0;
	while (Input[c] != '\0'){
		c++;
	}
	return c;	
}

int filenameValidation(char filename[]){
	int i;
	int length = stringlen(filename);
	char* Extension = (char*)malloc(5*sizeof(char)); 
	sprintf(Extension, "%*s", 4, filename + (length - 4));	
	if(length<5 || length >= 255 || strcmp(Extension, ".txt") != 0){
		printf("Wrong extension\n");
		return 0;
	}
	for(i = 0; i < length - 4; i++){
		if(isalpha(filename[i]) == 0 && isdigit(filename[i]) == 0){
			free(Extension);
			return 0;
		}
	}
	free(Extension);
	return 1;
}

void filenameInput(char filename[20]){
	char* Buffer = (char*)malloc(100*sizeof(char));
	printf("Please enter the file name.\nNOTE: only supports files with the [.txt] extension.\n");
	fgets(Buffer, 20, stdin);
	sscanf(Buffer, "%s", filename);
	if(filenameValidation(filename) == 0){
		printf("INVALID INPUT\n");
		filenameInput(filename);
	}
	free(Buffer);
}

int InputValidation(int input){
	if(input>0 && input <= 4){
		return 1;
	}
	else{
		return 0;
	}
}

void FileOperator(FILE *file, char** inputFile, int *Wordcount){
	int i, j;
	char *str = (char*) malloc(1000*sizeof(char));
	char **Words = (char**)malloc(5000*sizeof(char*));
	for(i = 0; i < 5000; ++i){
		Words[i] =  (char*)malloc(50*sizeof(char));
	}
	i = 0;
	j = 0;
	while( fgets(str, 1000, file) != NULL ){		
    		for(i = 0; i <= (strlen(str)); i++){
			if(*Wordcount == 5000){
				return;
			}
        		if(str[i] == ' ' || str[i] == '\0' || j == 15){
            			Words[*Wordcount][j]= '\0';
				*Wordcount += 1;
				j = 0;
			}
        		else{
            			Words[*Wordcount][j] = str[i];
            			j++;
        		}
    		}
	}
    	for(i = 0; i < *Wordcount; i++){

		for(j = 0; j <strlen(Words[i]); j++){
			if(j == 15){
				break;
			}
			else{
				inputFile[i][j] = tolower(Words[i][j]);
				
			}
		}
	}
	for(i = 0; i< *Wordcount; i++){
		free(Words[i]);
	}
	free(Words);
}

void Free(char **Input){
	int i;
	for(i = 0; i <strlen(*Input); i++){
		free(Input[i]);
	}
	free(Input);
}

int StrMatch(char* segment, char target){
	char* ptr;
	int index;
	ptr = strchr(segment, target);
	index = (int)(ptr - segment);
	if (ptr == NULL){
		return -1;
	}
	else{
		return index; 
	}
}

void CipherFileWrite(char* Cipher){
	FILE *fp;
	char *Name = (char*) malloc(20*sizeof(char));
	printf("Where would you like to save your Cipher to? ");
	filenameInput(Name);
	fp = fopen(Name, "w");
	fputs(Cipher, fp);
	fclose(fp);
}

void cipherWrite(int Check, char** inputFile, int *Wordcount){
	int size, i, j, k, check, randint, counter;
	char delim[] = " ";
	char *ptr;
	char c;
	char* coords = (char*)malloc(10*sizeof(char));
	char *Buffer = (char*)malloc(sizeof(char)*1500);
	char *CipherArray;
	srand(1090642);
	
	printf("Seeding with: 1090642\n\n");
	if(Check == 0){
		*Wordcount = 0;
		printf("Enter your cipher text, and press ENTER to submit:\n");
		fgets(Buffer, 1500, stdin);
		size = strlen(Buffer);
		ptr = strtok(Buffer, delim);
		while(ptr != NULL){	
			for(i = 0; i < strlen(ptr); i++){
				if( i < 15){
					if(ptr[i] == ' ' || ptr[i] == '\n'){
						inputFile[*Wordcount][i] = '\0';
					}
					else{
						inputFile[*Wordcount][i] = tolower(ptr[i]);
					}
				}
			}
			*Wordcount +=1;
			ptr = strtok(NULL, delim);
		}				
	free(Buffer);
	}
	randint = rand() % 10;
	size = 0;
	Buffer = (char*)malloc(sizeof(char)*1500);
	printf("Enter your secret message in plaintext and press ENTER to submit:\n");
	fgets(Buffer, 1500, stdin);
	CipherArray= (char*)malloc(((strlen(Buffer)*8)*1500));
	for(i = 0; i < strlen(Buffer); i++){
		randint = rand() % 10;
		counter = 0;
		if(Buffer[i] == ' ' || Buffer[i] == '\n'){
			size +=1;
			if(Buffer[i] == ' '){
				strcat(CipherArray, " ");
			}
			if(Buffer[i] == '\n'){
				strcat(CipherArray, "\n");
			}
			continue;
		}
		check = 0;
		c = Buffer[i];
		for(j = 0; j < *Wordcount; j++){
			if(check == 1){
				check = 0;
				break;
			}
			for(k = 0; k < strlen(inputFile[j]); k++){
				if(tolower(c) == inputFile[j][k]){
					if(counter == randint){
						sprintf(coords, "%d", j);
						strcat(CipherArray, coords);
						strcat(CipherArray, ",");
						sprintf(coords, "%d", k);
						strcat(CipherArray, coords);
						strcat(CipherArray, "|");
						printf("Letter: [%c], X: [%d] Y: [%d]\n", c, j, k);
						check = 1;
						counter = 0;
						break;
					}
					else{
						counter +=1;
					}
				}
				if(j == *Wordcount -1 && k == strlen(inputFile[i])-1 && counter == 0){
					printf("#\n");
					strcat(CipherArray, "#");
					check = 0;
					break;
				}
	
			}			
		}
	}
	CipherFileWrite(CipherArray);
	free(coords);
	free(Buffer);
	free(CipherArray);
}

void decrypt(int Check, char** inputFile, int *Wordcount){
	int i, row;
	char delim[] = " ";
	int row1 = 0;
	int row2 = 0;
	char *ptr;
	char *Buffer = (char*)calloc('*',sizeof(char)*1500);
	FILE *fp;
	char** Output = (char**)malloc(sizeof(char)*2);
	char *Name = (char*) malloc(20*sizeof(char));
	for(i = 0; i < 2; i ++){
		Output[i] = (char*)malloc(sizeof(char));
	}
	if(Check == 0){
		*Wordcount = 0;
		printf("Enter your cipher text, and press ENTER to submit:\n");
		fgets(Buffer, 1500, stdin);
		ptr = strtok(Buffer, delim);
		while(ptr != NULL){	
			for(i = 0; i < strlen(ptr); i++){
				if( i < 15){
					if(ptr[i] == ' ' || ptr[i] == '\n'){
						inputFile[*Wordcount][i] = '\0';
					}
					else{
						inputFile[*Wordcount][i] = tolower(ptr[i]);
					}
				}
			}
			*Wordcount +=1;
			ptr = strtok(NULL, delim);
		}				
	free(Buffer);
	}
	printf("\nWhat ENCRYPTED file do you want to decrypt? ");
	filenameInput(Name);
	fp = fopen(Name, "r");
	printf("\n");
	row = 0;
	while(fgets(Buffer, 1500, fp) != NULL){
		Buffer = realloc(Buffer, strlen(Buffer));
		for(i = 0; i < strlen(Buffer); ++i){
			if(Buffer[i] == ' ' || Buffer[i] == '\n' || Buffer[i] == '#'){
				printf("%c", Buffer[i]);
			}
			if(isdigit(Buffer[i])>0){
				if(row == 0){
					row1 = (row1 *10) + (Buffer[i] - '0');
				}
				else{
					row2 = (row2* 10) + (Buffer[i] - '0');
				}
			}
			if(Buffer[i] == ','){
				row +=1;
			}
			if(Buffer[i] == '|'){
				
				printf("%c", inputFile[row1][row2]);
				row1 = 0;
				row2 = 0;
				row = 0;
			}
		}
		free(Buffer);
		Buffer = (char*)malloc(1500*sizeof(char));
	}
	free(Buffer);
	fclose(fp);
}


void menu(int *input){
	char Buffer[100];
	printf("*********************************************************\n\n");
	printf("Please enter a Number: \n");
	printf(" 1) Read in the name of a text file to use as a cipher key\n");
	printf(" 2) Create a cipher using the input text file (and save the result to a file)\n");
	printf(" 3) Decode an existing cipher (prompt user for a file to read containing the cipher text)\n");
	printf(" 4) Exit the program\n");
	printf("\n*********************************************************\n");	
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%d", input);
	printf("\n");
	if(InputValidation(toupper(*input)) == 0 || isalpha(*input) != 0){
		printf("Invalid input. Please try again.\n");
		menu(input);
	}
}

void menuDriver(){
	FILE *fp;
	int Check = 0;
	int Wordcount, menuInput, i;
	char filename[20];
	char ** inputFile = (char**)malloc(5000*sizeof(char*));
	for(i = 0; i < 5000; ++i){
		inputFile[i] =  (char*)malloc(50*sizeof( char));
	}
	menu(&menuInput);
	while (menuInput != 4){
		if (menuInput == 4){
			break;
		}
		switch(menuInput){
			case 1:
				Check = 1;
				Free(inputFile);
				inputFile = (char**)malloc(5000*sizeof(char*));
				for(i = 0; i < 5000; ++i){
					inputFile[i] =  (char*)malloc(50*sizeof( char));
				}	
				filenameInput(filename);
				fp = fopen( filename, "r" );
				if (fp == NULL){
					printf("\nFile does not exist in this directory.\nReturning to Menu...\n\n");
        				break;
				}
				FileOperator(fp, inputFile, &Wordcount);
				fclose(fp);
				for(i = 0; i < Wordcount; i++){
					inputFile[i] = (char*)realloc(inputFile[i], strlen(inputFile[i])+1);					
				}
				inputFile = (char**)realloc(inputFile, Wordcount*8);
				menu(&menuInput);
				break;
			case 2:
				cipherWrite(Check, inputFile, &Wordcount);
				Check = 1;
				menu(&menuInput);
				break;
			case 3:
				decrypt(Check, inputFile, &Wordcount);
				Check = 1;
				menu(&menuInput);
				break;
			default:
				Free(inputFile);
				break;
		}
	}
}

int main(){
	menuDriver();
	printf("Thank you, goodbye.");
	return 0;
}