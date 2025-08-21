#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
  printf("Signal Handler Called!\n");
  exit(0);
}

int main() {
  struct sigaction sa = {0};
  sa.sa_handler = handler;
  sigaction(SIGINT, &sa, NULL);

  while(1) {
    printf(".");
    fflush(stdout); // Flushes the buffer to print .
    sleep(1);
  }
  return 0;
}
