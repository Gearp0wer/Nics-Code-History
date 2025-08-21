/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 5
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checker(char input[],char check[]){
    int i,result = 1;
    for(i = 0; i<3; i++) {
        if(input[i] != check[i]) {
            result=0;
            break;
        }
    }
    return result;
}

void input_letter(char *letter){
	char Buffer[100];

	printf("Enter the first letter of your last name[A-Z]: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", letter);
	printf("\n");
	*letter = toupper(*letter);
	if(isalpha(*letter) == 0 ){
		printf("%c IS NOT A VALID INPUT. PLEASE TRY AGAIN.\n\n", *letter);
		input_letter(letter);
	}
}

void input_month(char *BirthMonth){
	char Buffer[100];
	
	printf("Enter your birth month [JAN|FEB|...|DEC]: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%s", BirthMonth);
	printf("\n");
	BirthMonth[0] = toupper(BirthMonth[0]);
	BirthMonth[1] = toupper(BirthMonth[1]);
	BirthMonth[2] = toupper(BirthMonth[2]);
	if( checker(BirthMonth, "JAN") == 0 && checker(BirthMonth, "FEB") == 0 && checker(BirthMonth, "MAR") == 0 && checker(BirthMonth, "APR") == 0 &&
	checker(BirthMonth, "MAY") == 0 && checker(BirthMonth, "JUN") == 0 && checker(BirthMonth, "JUL") == 0 && checker(BirthMonth, "AUG") == 0 && 
	checker(BirthMonth, "SEP") == 0 && checker(BirthMonth, "OCT") == 0 && checker(BirthMonth, "NOV") == 0 && checker(BirthMonth, "DEC") == 0){
		printf("%s IS NOT A VALID INPUT. PLEASE TRY AGAIN.\n\n", BirthMonth);
		input_month(BirthMonth);
	}
}

void input_num(int *cellNum){
	char Buffer[100];
	
	printf("Enter the last digit of your cellphone [0-9]: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%d", cellNum);
	printf("\n");
	if(isalpha(*cellNum) != 0 || *cellNum < 0 || *cellNum > 9){
		printf("%d IS NOT A VALID INPUT. PLEASE TRY AGAIN.\n\n", *cellNum);
		input_num(cellNum);
	}
}

void get_adjective(char letter, char adjective[]){
	switch(letter){
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
			strcpy(adjective,"The Awesome");
			break;
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
			strcpy(adjective,"The Funny");
			break;
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
			strcpy(adjective,"The Dangerous");
			break;
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
			strcpy(adjective,"The Lovely");
			break;

		default:
			strcpy(adjective,"The Electrifying");
	}
}

void get_subject(char BirthMonth[], char Subject[]){
	if (strcmp("JAN",BirthMonth) == 0 || strcmp("FEB",BirthMonth) == 0 || strcmp("MAR",BirthMonth) == 0){
		strcpy(Subject,"Biography");
		return;
	}
	else if (strcmp("APR",BirthMonth) == 0 || strcmp("MAY",BirthMonth) == 0 || strcmp("JUN",BirthMonth) == 0){
		strcpy(Subject,"Revenge");
		return;
	}
	else if (strcmp("JUL",BirthMonth) == 0 || strcmp("AUG",BirthMonth) == 0 || strcmp("SEP",BirthMonth) == 0){
		strcpy(Subject,"Battle");
		return;
	}
	else{
		strcpy(Subject,"Fairy Tale");
		return;
	}
}

void get_complement(int cellNum, char complement[]){
	switch(cellNum){
		case 0:
		case 1:
			strcpy(complement,"of a Movie Star");
			break;
		case 2:
		case 3:
			strcpy(complement,"of a Hero");
			break;
		case 4:
		case 5:
			strcpy(complement,"of a Jedi");
			break;
		case 6:
		case 7:
			strcpy(complement,"of an Ogre");
			break;

		default:
			strcpy(complement,"of a Dreamer");
	}

}

void stringconcat(char adjective[], char Subject[], char complement[], char *movieTitle){
	movieTitle = strcat(movieTitle, adjective);
	movieTitle = strcat(movieTitle, " ");
	movieTitle = strcat(movieTitle, Subject);
	movieTitle = strcat(movieTitle, " ");
	movieTitle = strcat(movieTitle, complement);
}


int main(){
	char Buffer[100];
	#define SIZE  20
	#define WSIZE  50
	char adjective[SIZE], Subject[SIZE], complement[SIZE], movieTitle[WSIZE], BirthMonth[3];
	int cellNum;
	char letter;
	char esc = ' ';
	printf("\n*** Welcome to the Title Movie creator program ***\n\n");
	while(esc != 'Y' || esc != 'y'){
		if(esc == 'y' || esc == 'Y'){
			break;
		}
		input_letter(&letter);
		input_month(BirthMonth);
		input_num(&cellNum);

		get_adjective(letter, adjective);
		get_subject(BirthMonth, Subject);
		get_complement(cellNum, complement);
		stringconcat(adjective, Subject, complement, movieTitle);
		printf("The movie title for your life is:\n");
		printf("\t%s\n\n", movieTitle);

		printf("Do you want to quit [Y|y]? ");
		fgets(Buffer, 100, stdin); 
		sscanf(Buffer, "%c", &esc);
		printf("\n");

	}
	printf("Thank you, Good bye.\n");
	return 0;
}
