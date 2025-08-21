/* A sample program provided as local executable.
 * - Once started, this program will slowly print out a count-down
 *   until the counter reaches zero.
 * - The default initial counter value is 10.
 * - Optionally the user can specify the initial counter value.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define DEFAULT_COUNTER 10

// Prints X messages, then returns X
int main(int argc, char *argv[]){
  int counter = DEFAULT_COUNTER;

  if (argc == 2) {
    counter = strtol(argv[1], NULL, 10);
  }

  // Print a simple message, then sleep for 1 second between.
  int i = 0;
  for(i = 0; i < counter; i++) {
    printf("[PID: %d] slow_cooker count down: %d ...\n", getpid(), counter - i);
    sleep(1);
  }

  return counter;
}
