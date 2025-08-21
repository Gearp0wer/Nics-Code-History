#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 50

int main() {
  pid_t pid[N] = {0};
  int i = 0;
  int child_status = 0;
  for (i = 0; i < N; i++) {
    if ((pid[i] = fork ()) == 0) {
      exit (100 + i);		/* Child */
    }
  }
  for (i = 0; i < N; i++) {
    pid_t wpid = waitpid(pid[i], &child_status, 0);
    if (WIFEXITED (child_status)) {
      printf ("Child %d terminated with exit status %d\n",
               wpid, WEXITSTATUS (child_status));
    }
    else {
      printf ("Child %d terminate abnormally\n", wpid);
    }
  }
  return 0;
}
