/* Nicholas Locklear G01090642
 * CS 262 - 211
 * Lab 11 Function 1
 *
 * TODO: check dmalloc is allocating the correct amt [DONE]
 * create LL of delivery orders [DONE]
 * add in robot order allocation, data, validation to LL of deliveries [DONE]
 * write createItem [DONE]
 * write InsertItem [DONE]
 * write InsertItem's sorter and checker [DONE]
 * write printItems [DONE]
 * write Free() [DONE]
 */

/* Oops, this is late, and a bit messy, but I finally figured out Linked Lists so i'm happy. */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "orderlist_nlocklea_221.c"

typedef struct _robotOrder{
	unsigned int robotNum;
	orderList *data;
	char *deliverTo; 
	char *restaurant;
	struct _robotOrder *next;
	} robotOrder;


int stringlen(char Input[]){ /* does as named, returns the length of a string*/
	int c = 0;
	while (Input[c] != '\0'){
		c++;
	}
	return c;
}

/*----------These are 2 paired Free() methods used to free the robot node and then free the orderlists------------*/
void freeOrderlist(orderList *List) {
	foodNode *prev = List->head;
	foodNode *current = List->head;

	while(current){
		prev = current;
		current = prev->next;
		free(prev->data);
		free(prev->data);
	}
}

void freeRobots(robotOrder *head) {
	robotOrder *prev = head;
	robotOrder *current = head;

	while(current){
		prev = current;
		current = prev->next;
		free(prev->deliverTo);
		free(prev->restaurant);
		freeOrderlist(prev->data);
	}
}
/*-------------------------------------------------------------------*/

int StringValidation(char input[], int length){ /* this is the input validator for the robot number*/
	int i;
	if(input[0] == '\n'){
		return 0;
	}
	for(i = 0; i < length-1; i++){
		if(!isdigit(input[i]) || input[i] == '-'){
			return 0;
		}
	}
	return 1;
}

void numberInput(unsigned int *Number){ /* the actual input function for the robot number */
	char Buffer[100];
	int stringlength;
	printf("Robot Number: ");
	fgets(Buffer, 100, stdin); 
	stringlength = stringlen(Buffer);
	if(StringValidation(Buffer, stringlength) == 1){
		printf("\n");
		sscanf(Buffer, "%u", Number);	
	}
	else{
		printf("\nError: not valid robot number.\n");
		numberInput(Number);
	}
}

void deliveryInput(char* delivery){ /* takes a string as the input for the delivery location */
	char Buffer[100];
	printf("Delivery Address for New delivery order: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%[^\n]", delivery);
	printf("\n");
}

void restaurantInput(char* restaurant){  /* takes a string as the input for the restaurant */
	char Buffer[100];
	printf("Restaurant from which to pick up food: ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%[^\n]", restaurant);
	printf("\n");
}

robotOrder* RoombaOrder(robotOrder* Head){ /* sets each robot Order */
	unsigned int Number;
	char* delivery = (char*) dmalloc(100);
	char* restaurant = (char*) dmalloc(100);
	robotOrder* input = (robotOrder*) dmalloc(sizeof(robotOrder));
	numberInput(&Number);
	deliveryInput(delivery);
	restaurantInput(restaurant);
	input->robotNum = Number;
	input->data = createItem();
	input->deliverTo = delivery;
	input->restaurant = restaurant;	
	if(Head == NULL){
		input->next = NULL;
		return input;
	}
	else{
		input->next = Head;
		return input;
	}
}

void robotOutput(robotOrder *start){ /* prints the robot order data, and calls the OrderList print */
	robotOrder *currentNode = start;
	while(currentNode !=NULL){
		printf("Robot Number %d: Delivery order from %s has %d food item(s)\n", currentNode->robotNum, currentNode->restaurant, currentNode->data->count );
		printf("Deliver to: %s\n", currentNode->deliverTo);
		printItems(currentNode->data);
		currentNode = currentNode->next;
	}
	freeRobots(currentNode);
}
 	   
void menu(char *input){ /* the menu and input taker for the menu*/
	char Buffer[100];
	printf("New delivery order? (y/n) ");
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", input);
	printf("\n");
	if(*input != 'y' && *input != 'n'){
		printf("Invalid input. Please try again.\n");
		menu(input);
	}
}

void menuDriver(){ /* the driver function of the program*/
	char MenuInput;
	int count;
	robotOrder* OrderHead = NULL;
	MenuInput = ' ';
	menu(&MenuInput);
	while ( MenuInput != 'n' ){      
		if ( MenuInput == 'n' ){
			break;
		}      
		else{
			count +=1;
			OrderHead = RoombaOrder(OrderHead);
			menu(&MenuInput);
		}
	} 
	if(OrderHead == NULL){
		printf("No deliveries to be made :(\n");
	}
	else{
		printf("List of Deliveries: %d\n", count);
		robotOutput(OrderHead);
	}
	printf("Thank you, goodbye.");
}

int main(){
	printf("*****************************************************\n\n* Welcome to GMU's Starship Robots Delivery\n* Central Dispatch System\n"
"\n*****************************************************\n\n");
	menuDriver();
	return 0;
}