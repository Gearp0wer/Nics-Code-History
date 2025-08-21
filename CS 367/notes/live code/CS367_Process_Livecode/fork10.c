#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

// Clone this process, then turn it into cp! 
int main() {
  char *argv[MAX_ARGS] = {0};
  argv[0] = "cp";
  argv[1] = "fork1.c";
  argv[2] = "foo.c";
  argv[3] = 0;
  if (fork() == 0) {
     execv("/usr/bin/cp", argv);
  }
  waitpid(-1, NULL, 0); // Wait for any child, don't care about status (NULL)
  printf("copy completed\n");
  exit(0);
}
