/* 
 * Nicholas Locklear G01090642
 * Cs 211 - 221
 * Project 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "orderlist_nlocklea_221.h"

/* compares strings for alphabetical ordering */
int strcmpi(char *s, char *t){
	while (*s && tolower(*s) == tolower(*t)){
		s++;
		t++;
	}
	return tolower(*s) - tolower(*t);
}

/* allocates memory with a check for successful allocation */
void *dmalloc(size_t size){
	void *p = malloc(size);
	if (!p){
		printf("memory allocation failed\n");
		exit(1);
	}
	return p;
}

void swap(foodNode *a, foodNode *b){ /* minor func to swap the nodes */
    	char* temp = a->data;
    	a->data = b->data;
    	b->data = temp;
}

void bubbleSorter(foodNode *start){ /* standard bubble sort */
	int swapped;
	foodNode *ptr1;
	foodNode *lptr = NULL;
	if (start == NULL){
        	return;
	}
	do{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr){
			if (strcmpi(ptr1->data, ptr1->next->data) > 0){ 
                	swap(ptr1, ptr1->next);
                	swapped = 1;
            		}
            	ptr1 = ptr1->next;
        	}
        	lptr = ptr1;
    	}
    	while (swapped);
}

orderList *createItem(){ /* creates an orderlist, takes input of foods, and then returns an orderlist */
	char Buffer[100]; 
	char* foodName;
	orderList* newOrder = (orderList*) dmalloc(sizeof(orderList));
	newOrder->head = NULL;
	newOrder->count = 0;
	while(Buffer[0] != '\n'){
		printf("Food Item: ");
		fgets(Buffer, 100, stdin); 
		foodName = (char*) dmalloc(sizeof(Buffer));
		sscanf(Buffer, "%[^\n]", foodName);
		if(insert(foodName, &newOrder) == 0){
			printf("Item already in order.\n");
			continue;
		}
		else{
			newOrder->count += 1;
		}
	}
	bubbleSorter(newOrder->head);
	printf("%s\n", newOrder->head->data);
	newOrder->count -= 1;
	return newOrder;
}  

int insert(char *str, orderList **s){ /* the insert function, does not sort but does check for duplicates */
	foodNode* inputItem = (foodNode*) dmalloc(sizeof(foodNode));
	foodNode* headCopy = (foodNode*) dmalloc(sizeof(foodNode));
	int i;
	headCopy = (*s)->head;
	if(inputItem == NULL){
		printf("ERROR\n");
		exit(1);
	}
	if((*s)->head == NULL){
		inputItem->data = str;
		inputItem->next = (*s)->head;
		(*s)->head = inputItem;
		return 1;
	}
	else{
		for(i = 0; i < (*s)->count; i++){
			if(strcmpi(str, headCopy->data) == 0){
				return 0;
			}
			else{
				headCopy = headCopy->next;
			}	
		}
		inputItem->data = str;
		if(strcmpi(str, (*s)->head->data) >0){
			inputItem->next = (*s)->head->next;
			(*s)->head->next = inputItem;
			return 1;	
		}
		else{
			inputItem->next = (*s)->head;
			(*s)->head = inputItem;
			return 1;
		}
	}
	return 0;
}

void display(foodNode *start){ /* the actual display function, i wrote it when the program was still a mess */
	foodNode *currentNode = start;
	while(currentNode !=NULL){
		printf("%s\n", currentNode->data);
		currentNode = currentNode->next;
	}
	printf("\n");
}

void printItems(orderList *s){ /* links from the print, to the display method */
	foodNode *currentNode = s->head;
	display(currentNode);
}

