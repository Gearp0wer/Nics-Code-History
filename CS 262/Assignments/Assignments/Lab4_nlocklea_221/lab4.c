/******************************************************
 *  CS262  Lab 4
 *
 *  Name:  ________________________________
 *  Lab Section: _____________
 *
 * This program calculates the sum of the integers from
 * 0 up to (and including) an integer input by the user
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){
  //int i, count
  int i, count;
  //int sum = 0;
  int sum;
  char Buffer[100];

  printf("Enter an integer -> ");
  fgets(Buffer, 100, stdin);
  //sscanf(Buffer, "%d", count);
  sscanf(Buffer, " %d", &count);

  //for (i == 0; i < count; i++);{
  //for (i = 0; i < count; i++);{
  //for (i = 0; i < count; i++){
  for (i = 1; i <= count; i++){
    //sum = count;
    sum += i;
    printf("i = %d sum = %d\n", i, sum); // Added for Debugging
  }

  printf("The sum of integers 0 to %d is: %d\n", count, sum);

  return 0;
}