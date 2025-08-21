#include <types.h>
#include <lib.h>
#include <thread.h>
#include <syscall.h>
#include <curthread.h>

int
sys_getpid( int *retval ) {
	//int s;
	assert( curthread != NULL );
	assert( curthread->td_proc != NULL );
	//s = splhigh();
	*retval = curthread->p_pid;
	//splx(s);
	//kprintf(curthread->p_pid);
	//kprintf(0);
	return 0;
}