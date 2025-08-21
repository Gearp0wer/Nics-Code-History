#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Clone this process, then turn it into cp! 
int main() {
   if (fork() == 0) {
      execl("/usr/bin/cp", "cp", "fork1.c", "foo.c", 0);
   }
   waitpid(-1, NULL, 0); // Wait for any child, don't care about status (NULL)
   printf("copy completed\n");
   exit(0);
}
