#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
   int child_status = 0;
   pid_t child_pid = fork();
   if (child_pid == 0) {
      printf("HC: hello from child\n");
   }
   else {
      printf("HP: hello from parent\n");
      waitpid(child_pid, &child_status, 0);
      printf("CT: child has terminated\n");
   }
   exit(0);
}
