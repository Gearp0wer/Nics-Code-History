#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILDREN 10
static int child_count = 0;

void reaper(int sig) {
  int status = 0;
  pid_t pid = waitpid(-1, &status, 0);
  child_count--;
  printf("Process %d Exited.\n", pid);
}

int main() {
  struct sigaction sa = {0};
  sa.sa_handler = reaper;
  sigaction(SIGCHLD, &sa, NULL);
  for(int i = 0; i < CHILDREN; i++) {
    child_count++;
    if(fork() == 0) {
      exit(0);
    }
  }

  while(child_count > 0) {
    printf("Still %d Children Left\n", child_count);
    sleep(1);
  }
  printf("%d Children Left!\n", child_count);
  return 0;
}
