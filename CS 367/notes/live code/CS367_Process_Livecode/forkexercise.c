#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = 0;
  printf("A\n");
  // Run fork, then assign the return to pid, then check if pid > 0
  if((pid = fork())) {
    waitpid(pid, NULL, 0);
    printf("B\n");
  } else {
    printf("C\n");
  }
  fork();
  printf("D\n");
  return 0;
}
