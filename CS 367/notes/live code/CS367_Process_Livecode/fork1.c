#include <stdio.h>
#include <unistd.h> // Linux API Headers!

int main () {
  printf("Hi\n");
  if (fork() == 0) { 
    printf("Hello from the Child!\n"); // Child Process Starts here after fork()
  } else {
    printf("Hello from the Parent!\n");// Parent Process Continues here after fork()
  }

  return 0;
}
