#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static int has_terminated = 0;

void reaper(int sig) {
  printf("Got Signal that a Child Terminated.\n");
  printf("Reaping Process Now.\n");
  pid_t pid = waitpid(-1, NULL, 0);
  printf("Reaped PID %d\n", pid);
  has_terminated = 1;
}

int main() {
  struct sigaction sa = {0};
  sa.sa_handler = reaper;
  sigaction(SIGCHLD, &sa, NULL);

  pid_t pid = fork();
  if(pid == 0) {
    sleep(2);
    printf("Child Terminating now\n");
    exit(0);
  }

  while(has_terminated == 0) {
    printf(".");
    fflush(stdout); // Flushes the buffer to print .
    sleep(1);
  }
  printf("Child has terminated!\n");
  return 0;
}
