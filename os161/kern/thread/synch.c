/*
 * Synchronization primitives.
 * See synch.h for specifications of the functions.
 */

#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <curthread.h>
#include <machine/spl.h>
#include <queue.h>
////////////////////////////////////////////////////////////
//
// Semaphore.






struct semaphore *
sem_create(const char *namearg, int initial_count)
{
	struct semaphore *sem;

	assert(initial_count >= 0);

	sem = kmalloc(sizeof(struct semaphore));
	if (sem == NULL) {
		return NULL;
	}

	sem->name = kstrdup(namearg);
	if (sem->name == NULL) {
		kfree(sem);
		return NULL;
	}

	sem->count = initial_count;
	return sem;
}

void
sem_destroy(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	spl = splhigh();
	assert(thread_hassleepers(sem)==0);
	splx(spl);

	/*
	 * Note: while someone could theoretically start sleeping on
	 * the semaphore after the above test but before we free it,
	 * if they're going to do that, they can just as easily wait
	 * a bit and start sleeping on the semaphore after it's been
	 * freed. Consequently, there's not a whole lot of point in 
	 * including the kfrees in the splhigh block, so we don't.
	 */

	kfree(sem->name);
	kfree(sem);
}

void 
P(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	/*
	 * May not block in an interrupt handler.
	 *
	 * For robustness, always check, even if we can actually
	 * complete the P without blocking.
	 */
	assert(in_interrupt==0);

	spl = splhigh();
	while (sem->count==0) {
		thread_sleep(sem);
	}
	assert(sem->count>0);
	sem->count--;
	splx(spl);
}

void
V(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);
	spl = splhigh();
	sem->count++;
	assert(sem->count>0);
	thread_wakeup(sem);
	splx(spl);
}

////////////////////////////////////////////////////////////
//
// Lock.




struct lock *
lock_create(const char *name)
{
	struct lock *lock;
	kprintf("\nHEY IM HERE!\n");
	lock = kmalloc(sizeof(struct lock));
	if (lock == NULL) {
		return NULL;
	}

	lock->name = kstrdup(name);
	if (lock->name == NULL) {
		kfree(lock);
		return NULL;
	}
	
	// add stuff here as needed
	lock->waiting_threads = q_create(1);
	lock->lock_held = 0;
	lock->current_holder = NULL;
	return lock;
}

void
lock_destroy(struct lock *lock)
{
	int spl = splhigh();
	assert(lock != NULL);
	assert(lock->current_holder == NULL);
	
	//assert(isVehicleQueueEmpty(lock->waiting_threads));

    	//destroyVehicleQueue(lock->waiting_threads);

	//assert(lock != NULL);

	// add stuff here as needed
	q_destroy(lock->waiting_threads);
	kfree(lock->waiting_threads);	
	kfree(lock->name);
	kfree(lock);

	splx(spl);
}

void
lock_acquire(struct lock *lock)
{
	assert(lock != NULL);
	int spl = splhigh();
	int lockQueued = 0;
	assert(!lock_do_i_hold(lock));
	while(lock->lock_held == 1){
		if (lockQueued == 0){
			q_addtail(lock->waiting_threads, curthread);
			//q_grow(lock->waiting_threads,lock->waiting_threads->size+1 );

			lockQueued ++;
		}
		thread_sleep(q_getguy(lock->waiting_threads,q_getend(lock->waiting_threads)));
	}
	lock->lock_held = 1;
	lock->current_holder = curthread;
	splx(spl);

	//kprintf("\nLOCK ACQUIRED!\n");
}

void
lock_release(struct lock *lock)
{
	int spl = splhigh();
	assert(lock != NULL);
	assert(lock->lock_held && (lock->current_holder == curthread));
	lock->lock_held = 0;
	lock->current_holder = NULL;
	thread_wakeup(q_getguy(lock->waiting_threads,q_getstart(lock->waiting_threads)));
	q_remhead(lock->waiting_threads);
	splx(spl);	
}

int
lock_do_i_hold(struct lock *lock)
{
	assert(lock != NULL);
	return (lock->lock_held && (lock->current_holder == curthread));
	// Write this

	//(void)lock;  // suppress warning until code gets written

	//return 0;    // dummy until code gets written
}


////////////////////////////////////////////////////////////
//
// CV


struct cv *
cv_create(const char *name)
{
	struct cv *cv;

	cv = kmalloc(sizeof(struct cv));
	if (cv == NULL) {
		return NULL;
	}

	cv->name = kstrdup(name);
	if (cv->name==NULL) {
		kfree(cv);
		return NULL;
	}
	
	// add stuff here as needed
	
	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);

	// add stuff here as needed
	
	kfree(cv->name);
	kfree(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}
