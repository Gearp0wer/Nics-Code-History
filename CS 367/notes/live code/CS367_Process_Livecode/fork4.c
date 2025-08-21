#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Bonus! This is a cleanup function that is called if your program dies.
void cleanup(void) {
   printf("[PID: %d] Cleaning up\n", getpid());
}

int main() {
   atexit(cleanup); // On any exit from this program, it will call cleanup()
   fork();
   printf("[PID: %d] Going to exit now!\n", getpid());
   exit(0);
}
