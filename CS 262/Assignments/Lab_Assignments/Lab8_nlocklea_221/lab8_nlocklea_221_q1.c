/*
 *Nicholas Locklear
 *G01090642
 *Lab 8 q1
 *CS 262 - 221
 */


#include <stdio.h>

#define MAX_SIZE 100 

int main()
{
    int arr[MAX_SIZE];
    int N, i;
    int * ptr = arr;    
    printf("Enter size of array: ");
    scanf("%d", &N);

    printf("Enter elements in array:\n");
    for (i = 0; i < N; i++)
    {
        // (ptr + i) is equivalent to &arr[i]
        scanf("%d", (ptr + i));
    }

    printf("Array elements: ");
    for (i = 0; i < N; i++)
    {
        // *(ptr + i) is equivalent to arr[i]
        printf("%d, ", *(ptr + i));
    }

    return 0;
}