/* 
 * Nicholas Locklear
 * G01090642
 * Lab 10
 * CS 262 - 211
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeInfo {
	char Name[50];
	int dob;
	int mob;
	int yob;
	struct NodeInfo *NxtPtr;
}Data;

int stringlen(char Input[]){
	int c = 0;
	while (Input[c] != '\0'){
		c++;
	}
	return c;
}

int StringValidation(char input[], int length){
	int i;
	if(input[0] == '\n'){
		return 0;
	}
	for(i = 0; i < length-1; i++){
		if(isdigit(input[i]) == 0 ){
			return 0;
		}
	}
	return 1;
}

void Validation(Data newData){
	char Buffer[100];
	
}

int insertNode(Data **start, Data newData){
        Data *newNode =  (Data*)malloc(sizeof(Data));
	if(newNode == NULL){
		printf("ERROR\n");
		return 0;
	}


/* ask for name, then search for equality, then insert */

	if(start == NULL){
		strcpy(newNode->Name, "Nicholas");
		newNode->dob = 10;
		newNode->mob = 7;
		newNode->yob = 1998;
		newNode->NxtPtr = NULL;
	        *start = newNode; 
		return 1;
	}
	else{
		strcpy(newNode->Name, "Nicholas");
		newNode->dob = 10;
		newNode->mob = 7;
		newNode->yob = 1998;
		newNode->NxtPtr = *start;
                *start=newNode; 
		return 1;
	}
	return 0;
}
/*
Data* deleteNode(Data **firstData, Data data){
	Data *placehold;
	return *placehold;
}
*/
void printList(){
}

int InputValidation(char input){
	if(input == '1' || input == '2' || input == '3' || input == '4'){
		return 1;
	}
	else{
		return 0;
	}
}

void menu(char *input, int *NumofFriends){
	char Buffer[100];
	
	printf("************ Friend's Birthday List ************\n\n");
	printf("Friends in the list: %d\n", *NumofFriends);
	printf("'1' - insert data\n'2' - delete data\n'3' - print data\n'4' - exit the program\n");
	printf("\n*********************************************************\n");
	printf("Please enter your choice: \n");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", input);
	printf("\n");
	if(InputValidation(*input) == 0 || isalpha(*input) == 1){
		printf("Invalid input. Please try again.\n");
		menu(input, NumofFriends);
	}
	*input = toupper(*input);
}

void menuDriver(){
	int NumofFriends;
	Data *Head;
	Data Current;
	char MenuInput;
	int nodecheck = 0;
	NumofFriends = 0;
	*Head = NULL;
	Current = NULL;
	MenuInput = ' ';
	
	menu(&MenuInput, &NumofFriends);
	while ( MenuInput != '4' ){
		if ( MenuInput == '4' ){
			break;
		}
		switch(MenuInput){
			case '1':
				insertNode(&Head, Current);
				menu(&MenuInput, &NumofFriends);
				break;
			case '2':
				menu(&MenuInput, &NumofFriends);
				break;
			case '3':
				menu(&MenuInput, &NumofFriends);
				break;
			default:
				break;
		}
	}
	printf("Thank you, goodbye.");
}

int main(){
	menuDriver();
	return 0;
}