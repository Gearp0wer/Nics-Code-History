/* Nicholas Locklear G01090642
 * CS 262 - 211
 * Lab 11 Function 1
 */

#include <stdio.h>
#include <stdlib.h>
#include "Function1.h"
#include "Lab11.h"

void Function1(){
        int i = 0;
        int *p = (int *) malloc(sizeof(int) * ARRAY_SIZE);
        if (p == NULL)
        {
           fprintf(stderr, "Function1(): Error allocating p\n");
           exit(1);
        }

        printf("In Function1()...\n");

        // Initialize the array
        for (i=0; i<ARRAY_SIZE; i++)
        {
            p[i]=i;
        }

        // Print part of the array
        for (i=0; i<PARTIAL_SIZE; i++)
        {
            printf("function1(): %s = %d,%s = %d ", PR(i),i,PR(p[i]), p[i]);
           printf("\n");
        }
  
        free(p);
}


