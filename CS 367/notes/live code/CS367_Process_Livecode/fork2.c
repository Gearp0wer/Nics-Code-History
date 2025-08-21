#include <stdio.h>
#include <unistd.h> // Linux API Headers

int main() {
    int x = 1;
    pid_t pid = fork(); // pid_t is an int in Linux
    // Each Process has Completely Separate Memory (globals, locals, etc)
    if (pid == 0) {
	    printf("[%d] Child has x = %d\n", getpid(), ++x); // getpid() return PID
    } else {
	    printf("[%d] Parent has x = %d\n", getpid(), --x);
    }
    printf("[%d] Bye from process with x = %d\n", getpid(), x);
    return 0;
}
