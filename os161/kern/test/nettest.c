/*
 * Network test code.
 */
#include <types.h>
#include <lib.h>
#include <test.h>

int
nettest(int argc, char **argv)
{
	(void)argc;
	(void)argv;	
	kprintf("No network support available\n");

	return 0;
}
