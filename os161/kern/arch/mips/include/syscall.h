#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int	sys_getpid( int * );
void	sys__exit( int );
int	sys_waitpid( int, userptr_t, int, int * );
int	sys_fork( struct trapframe *, int * );
int	sys_execv( userptr_t, userptr_t );

/**
 * Kernel versions of the system calls.
 */
int	___waitpid( int, int *, int );
#endif // _SYSCALL_H_ 
