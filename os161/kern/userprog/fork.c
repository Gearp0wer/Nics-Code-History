#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <array.h>
#include <machine/spl.h>
#include <machine/pcb.h>
#include <thread.h>
#include <curthread.h>
#include <scheduler.h>
#include <addrspace.h>
#include <vnode.h>
#include <machine/trapframe.h>


static
int
trapframe_clone( struct trapframe *tf, struct trapframe **newtf ) {
	*newtf = kmalloc( sizeof( struct trapframe ) );
	if( *newtf == NULL )
		return ENOMEM;
	memcpy( *newtf, tf, sizeof( struct trapframe ) );
	return 0;
}

void md_forkentry(struct trapframe *tf){
	tf->tf_v0 = 0;
	tf->tf_a3 = 0;
	tf->tf_epc += 4;
	mips_usermode( tf );
}

void
md_forkChild(void *tf, unsigned long addrsPtr){
	struct addrspace *newAdrs = (struct addrspace *) addrsPtr;
	as_copy( newAdrs, &curthread->t_vmspace );
	as_activate( curthread->t_vmspace );
	md_forkentry(tf);
}


pid_t sys_fork(struct trapframe *parent_tf, int *returnPID){
	struct thread parentThread = *curthread;
	int retval;
	struct trapframe *tf_new = NULL;
	returnPID = NULL;
	trapframe_clone( parent_tf, &tf_new );
	retval = thread_fork(parentThread.t_name,  (void*) tf_new, (long unsigned) parentThread.t_vmspace, md_forkChild, NULL);
	if (retval == ENOMEM || retval == EAGAIN){
		*returnPID = retval;
		return -1;
	}
	return retval;
}
