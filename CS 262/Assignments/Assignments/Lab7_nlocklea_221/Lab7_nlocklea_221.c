/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 7
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* NOTES:
I included a lot of helper functions for this, my goal was to keep each func at ~20 lines. Here's what they all do:
typedef: defines the item type
InputValidation: input validation func specifically for the menu options. I probably could condense this.
stringlen: I needed a reliable way of getting the length of a string
StringValidation: I needed a way to make sure that my input was only integers and contained no letters. 
Item output: what the search function outputs
Item(Price/Quantity/Name/ID)input: the input functions I use to build each item and validate it
ItemConstructor: a function solely for making new items.
menu: the menu function, main switchboard
Insert item: does as Lab documentation states.
Search item: does as Lab documentation states. 
Update item: does as Lab documentation states.

Todo: broken validation (again) for the ints. shouldnt take naked newlines in ID, name, price or quantity.
*/

int Size = 0;

struct Item {
	int itemId;
	char itemName[20];
	int quantity;
	double pricePerItem;
};

typedef struct Item Item;
int InputValidation(char input){
	switch(input){
	case 'I':
	case 'U':
	case 'S':
	case 'D':
	case 'Q':
		return 1;
	default :
		return 0;
	}
}

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

void ItemOutput(Item item){
	printf("\n********************\n");
	printf("item id: %02d\n", item.itemId);
	printf("item Name: %s\n", item.itemName);
	printf("item quantity: %d\n", item.quantity);
	printf("item Price: %.2f\n", item.pricePerItem);
	printf("********************\n\n");
}

void ItemPriceInput(Item *item){
	char Buffer[100];
	printf("Enter Item Price: ");
	fgets(Buffer, sizeof(Buffer), stdin);
	sscanf(Buffer, "%lf", &item->pricePerItem);
	if(isalpha(item->pricePerItem) != 0 || item->pricePerItem < 0 ){
		printf("%.2f IS NOT A VALID INPUT. PLEASE TRY AGAIN.\n\n", item->pricePerItem);
		ItemPriceInput(item);
	}
}

int ItemQuantityInput(){
	char Buffer[100];
	int length;
	int quantity = 0;
	printf("Enter item Quantity: ");
	fgets(Buffer, 100, stdin); 
	length = stringlen(Buffer);		
	if(StringValidation(Buffer, length) == 0){
		printf("Invalid input\n");
		return ItemQuantityInput();
	}
	else{
		sscanf(Buffer, "%d", &quantity);		
	}
	return quantity;
}

void ItemNameInput(Item *item){
	char Buffer[100];
	printf("Enter Item Name: ");
	fgets(Buffer, 20, stdin);
	sscanf(Buffer, "%s", item->itemName);	
}

int ItemIDInput(){
	char Buffer[100];
	int length;
	int ID = 0;
	printf("Enter item ID: ");
	fgets(Buffer, 100, stdin); 
	length = stringlen(Buffer);		
	if(StringValidation(Buffer, length) == 0){
		printf("Invalid input\n");
		return ItemIDInput();
	}
	else{
		sscanf(Buffer, "%d", &ID);		
	}
	return ID;
}

void ItemConstructor(Item *Input){
	Input->itemId = ItemIDInput();
	ItemNameInput(Input);
	Input->quantity = ItemQuantityInput();
	ItemPriceInput(Input);
}

void menu(char *input){
	char Buffer[100];
	printf("*********************************************************\n\n");
	printf("Please enter a character: \n");
	printf("'i' - insert an item\n'u' - update the database\n's' - search the database\n'd' - display the database\n'q' - exit the program\n");
	printf("\n*********************************************************\n");
	
	fgets(Buffer, 100, stdin); 
	sscanf(Buffer, "%c", input);
	printf("\n");
	if(InputValidation(toupper(*input)) == 0 || isalpha(*input) == 0){
		printf("Invalid input. Please try again.\n");
		menu(input);
	}
	*input = toupper(*input);
}

void insertItem(Item *itemInventory, Item item){
	int i;
	for(i = 0; i <= Size; i++){
		if(itemInventory[i].itemId == item.itemId){
		printf("\nError Inserting an Item.\n\n");
		return;
		}
		else if(i == Size){
			itemInventory[i] = item;
		}
	}
}

void searchItem(Item *itemInventory, int itemID){
	int i;
	for(i = 0; i < Size; i++){
		if(itemInventory[i].itemId == itemID){
			ItemOutput(itemInventory[i]);
			return;
		}
	}
	printf("Item Not Found\n\n");
}

void updateItem(Item *itemInventory, int itemID, int quantity){
	int i;
	for(i = 0; i < Size; i++){
		if(itemInventory[i].itemId == itemID){
			itemInventory[i].quantity = quantity;
			ItemOutput(itemInventory[i]);
			return;
		}
	}

	printf("Item Not Found\n\n");
}

void printData(Item *itemInventory){
	int i;
	printf("*********************************************************\n");
	printf("Item ID    Item Name\tItem Quantity\tItem Price\n");
	printf("*********************************************************\n");
	for(i = 0; i < Size; i++){
		printf("%03d\t\t\"%s\"\t\t%d\t\t$%.02f\n\n",itemInventory[i].itemId, itemInventory[i].itemName, itemInventory[i].quantity, itemInventory[i].pricePerItem);
		
	}
}

void quit(Item *itemInventory){
	free(itemInventory);
	return;
}

int main(){
	Item item;
	int N = 5;
	char MenuInput;
	Item *itemInventory = malloc(sizeof(Item)*N);
	menu(&MenuInput);
	while ( MenuInput != 'q' || MenuInput != 'Q'){
		if ( MenuInput == 'q' || MenuInput == 'Q'){
			break;
		}
		switch(MenuInput){
			case 'I':
				if(N == Size){
					N = N*2;					
					itemInventory = (Item *) realloc(itemInventory, sizeof(item)*N);
				}
				ItemConstructor(&item);
				insertItem(itemInventory, item);
				Size +=1;
				menu(&MenuInput);
				break;
			case 'U':
				updateItem(itemInventory, ItemIDInput(), ItemQuantityInput());
				menu(&MenuInput);
				break;
			case 'S':
				searchItem(itemInventory, ItemIDInput());
				menu(&MenuInput);
				break;
			case 'D':
				printData(itemInventory);
				menu(&MenuInput);
				break;
			default:
				quit(itemInventory);
				break;
		}
	}
	printf("Thank you, goodbye.");
	return 0;
}