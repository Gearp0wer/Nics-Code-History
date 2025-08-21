#include <types.h>
#include <lib.h>
#include <thread.h>
#include <syscall.h>
#include <curthread.h>

int sys_getppid( ) {
	assert( curthread != NULL );	
	if(curthread->td_proc == NULL ){return -1;} //parent mia
	if(curthread->td_proc->p_is_dead == 1 ){return -1;}//dead parent
	else{
		return curthread->td_proc->p_pid;}

}