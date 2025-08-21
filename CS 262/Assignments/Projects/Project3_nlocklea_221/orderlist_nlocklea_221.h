/* 
 * Nicholas Locklear
 * G01090642
 * CS 262 - 211
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef ORDERLIST_NLOCKLEA_221_H
#define ORDERLIST_NLOCKLEA_221_H

typedef struct _foodNode{
	char *data; 
	struct _foodNode *next;
} foodNode;

typedef struct _orderList{
	foodNode *head; 
	int count;
} orderList;

orderList *createItem();

int insert(char *str, orderList **s);

void printItems(orderList *s);

#endif
