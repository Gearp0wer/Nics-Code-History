#include <stdio.h>
#include <stdlib.h>

#define SIZE (10)

typedef struct _debugLab
{
    int i;
    char c;
} debugLab;


// Prototypes
void PrintUsage(char *);
void DebugOption1(void);
void DebugOption2(void);

int main(int argc, char **argv)
{
    int option = 0;

    if (argc == 1)
    {
        PrintUsage(argv[0]);
	exit(0);
    }

    option = atoi(argv[1]);

    if (option == 1)
    {
	DebugOption1();
    }
    else if (option == 2)
    {
	DebugOption2();
    }
    else
    {
        PrintUsage(argv[0]);
        exit(0);
    }
}

void PrintUsage(char *command)
{
	fprintf(stderr, "Usage: %s [1 2]\n", command);
	fprintf(stderr, "           1 = Mode 1\n");
	fprintf(stderr, "           2 = Mode 2\n");
}

void DebugOption1()
{
    int i, j;
    int sum = 0;
    char charArray[SIZE];

    fprintf(stdout, "Here we are in DebugOption1()\n");

    
    for (i = 0; i < SIZE; i++)
    {
	sum += sum + i;
    }

    fprintf(stdout, "The sum of integers from 0 to %d is: %d\n", SIZE, sum);

}

void DebugOption2()
{
    debugLab *dl1 = NULL;
    debugLab *dl2 = malloc(sizeof(debugLab)); // Always check for a NULL Pointer after a call to malloc
    debugLab dl3;

    dl3.i = 37;
    dl3.c = 'A';
    dl2->i = 36;
    dl2->c = 'B';
    dl1->i =35;   // Oops! dl1 is NULL!
    dl1->c = 'C';

}
