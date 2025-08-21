/* A simple Makefile
* Nicholas Locklear G01090642
* Cs262, 221
* Project 1
* The compiler: gcc for C programs
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


void titleprinter(){
	printf("*****************************************************\n\n");
	printf("* Welcome to a simplified version of\n* Craps game\n");
	printf("*****************************************************\n");
}

void Seeder(int *Seed){

/*I really hope not having input validation doesnt bite me in the ass */

	char Buffer[100];
	printf("Please enter a random number: "); 
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%d", Seed);
	printf("\n");

}

int Better(int *Account_Bal){

/* this func is what sets the bet*/

	int Bet = 0;
	char Buffer1[100];
	printf("Make a bet \">=5 and <=100\"\n");
	fgets(Buffer1, 100, stdin); 
	sscanf(Buffer1, " %d", &Bet);
	if(Bet > *Account_Bal || Bet < 5){
		printf("Invalid amount.\n");
		return Better(Account_Bal);
	}
	printf("\n\n");
	printf("You have made a bet for: $%d\n", Bet);
	printf("\n\n");
	return Bet;
}

void menu(char *mode){

/* This function sets the mode for the game */

	char Buffer[5];

	printf("Enter your choice:\n");
	printf("1 - Pass Line\n");
	printf("2 - Do not Pass Line\n");
	printf("3 - Quit\n");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", mode);
	printf("\n");
	switch(*mode){
		case('1'):
			printf("You chose 1 - \"Pass Line\"\n\n");
			break;
		case('2'):
			printf("You chose 2 - \"Do not Pass Line\"\n\n");
			break;
		case('3'):
			printf("You chose 3 - \"Quit\"\n\n");
			break;
		default:
			printf("Invalid Selection.\n");
			menu(mode);
			break;
	}	
}

int roll(){

/* This rolls the dice*/

	int die_roll1;
	int die_roll2;
	int total;
	char Buffer[1]; 
	char myInt = ' '; 
 
	printf("Please press Enter to roll the dice:");

	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", &myInt); 
	if (myInt == '\n'){
		printf("Rolling . . .\n");
		die_roll1 = (rand() % 6) + 1;
		printf("Dice 1 - %d\n", die_roll1);

		die_roll2 = (rand() % 6) + 1;
		printf("Dice 2 - %d\n", die_roll2);

		total = die_roll1 + die_roll2;
		printf("Roll total = %d\n\n", total);
	}
	else{
		printf("Invalid.\n");
		roll();
	}
	return total;
}

int ruling(int *Account_Bal){
/*
* look, I'm really sorry. 
* This func is divided into two halves, pass line and dont pass line.
* both sit in a while loop to check for letting it ride 
*/

	int total = 0;
	int point = 0;
	int rolled;
	char mode;
	int Bet = 0;
	char Buffer1[100];
	char input = ' ';
	char letitride = ' ';

	Bet += Better(Account_Bal);
	menu(&mode);
	if(mode == '3'){
		return 0;
	}
	while(letitride != 'n' || letitride != 'N'){
		rolled = roll();
		if( mode == '1'){
			if(rolled==7 || rolled==11){
				printf("Congratulations you won $%d\n", Bet);
				if (Bet*2 <= *Account_Bal ){
					printf("Do you want to let it ride? (Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
					fgets(Buffer1, 100, stdin); 
					sscanf(Buffer1, "%c", &input);
					printf("\n");
					if(input == 'Y' || input == 'y'){
						Bet *=2;
						continue;
					}
				}
				else{
					total += Bet;
					return total;
				}

			}
			else if(rolled==2 || rolled==3 || rolled==12){
				printf("You lost $%d\n", Bet);
				total -= Bet;
				return total;
				}
			else{
				point = rolled;
				if (Bet*2 <= *Account_Bal ){
					printf("Do you want to double your bet?(Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
					fgets(Buffer1, 100, stdin); 
					sscanf(Buffer1, "%c", &input);
					printf("\n");
					if(input == 'Y' || input == 'y'){
						Bet *=2;
					}
				}
				do{
					rolled = roll();
					printf("\n\n");
					if(rolled==point){
						printf("Congratulations you won $%d\n", Bet);
						if (Bet*2 <= *Account_Bal ){
							printf("Do you want to let it ride? (Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
							fgets(Buffer1, 100, stdin); 
							sscanf(Buffer1, "%c", &input);
							printf("\n");
							if(input == 'Y' || input == 'y'){
								Bet *=2;
								continue;
							}
						}
					}	
					else{
						total += Bet;
						return total;
					}
				}while(rolled != 7);
				printf("You lost $%d\n", Bet);
				total -= Bet;
			}
		}
		else{
			if(rolled==7 || rolled==11){
				printf("You lost $%d\n", Bet);
				total -= Bet;
				return total;
			}
			else if(rolled==2 || rolled==3 || rolled==12){
				printf("Congratulations you won $%d\n", Bet);
				if (Bet*2 <= *Account_Bal ){
					printf("Do you want to let it ride? (Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
					fgets(Buffer1, 100, stdin); 
					sscanf(Buffer1, "%c", &input);
					printf("\n");
					if(input == 'Y' || input == 'y'){
						Bet *=2;
						continue;
					}
				}
				total += Bet;
				return total;

			}
			else{
				point = rolled;
				if (Bet*2 <= *Account_Bal ){
					printf("Do you want to double your bet?(Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
					fgets(Buffer1, 100, stdin); 
					sscanf(Buffer1, "%c", &input);
					printf("\n");
					if(input == 'Y' || input == 'y'){
						Bet *=2;
					}
				}
				do{
					rolled = roll();
					printf("\n\n");
					if(rolled==7){
						printf("Congratulations you won $%d\n", Bet);
						printf("Do you want to let it ride? (Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\")\n");
						fgets(Buffer1, 100, stdin); 
						sscanf(Buffer1, "%c", &letitride);
						if(letitride == 'Y' || letitride == 'y'){
							printf("\n\n");
							continue;
						}

						total += Bet;
						return total;
					}
				}while(point != rolled);
				printf("You lost $%d\n", Bet);
				total -= Bet;
			}
		}
	}
	return total;
}


int main(){
	char Buffer1[100];
	int Seed;
	int Account_Bal = 100;
	char input = ' ';
	int winnings = 0;

	titleprinter();
	Seeder(&Seed);
	srand(Seed);
	printf("%d\n", Seed);
	while(Account_Bal >0 || input != 'y' || input != 'Y'){
		if(Account_Bal<= 0){
			printf("GAME OVER\n");
			return 0;
		}
		if( input == 'y' || input == 'y'){
			printf("Thank you for playing!\n");
			break;
		}
		else{
			winnings = ruling(&Account_Bal);
			Account_Bal += winnings;

			if(winnings <0){
				printf("You have $%d\n", Account_Bal);
				printf("Do you want to quit?(Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
				fgets(Buffer1, 100, stdin); 
				sscanf(Buffer1, "%c", &input);
				printf("\n");
			}

			else if(winnings == 0){
				break;
			}

			else{
				printf("You have $%d\n", Account_Bal);
				printf("Do you want to quit?(Enter \"Y/y\" for \"Yes\" or \"N/n\" for \"No\"\n");
				fgets(Buffer1, 100, stdin); 
				sscanf(Buffer1, "%c", &input);
				printf("\n");
			}	
		}
	}
    	return 0;
}

