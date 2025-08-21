/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 */


/*
 * 
 * Includes
 *
 */

#include "stoplight_framework.h"

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <machine/spl.h>
#include <curthread.h>
#include <synch.h>

int vehicleCount;
struct lock *AB, *BC, *CA, *completionLock;
unsigned long curNum;





/*
 *
 * Function Definitions
 *
 */

/*
 * turn_left()
 *
 * Arguments:
 *      unsigned long vehiclenumber: the vehicle id number for fetching vehicle info.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turn_left(unsigned long vehiclenumber)
{
	/*
	 * Avoid unused variable warnings.
	 */

	(void) vehiclenumber;
}


/*
 * turn_right()
 *
 * Arguments:
 *      unsigned long vehiclenumber: the vehicle id number for fetching vehicle info.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turn_right(unsigned long vehiclenumber, int route){
	//kprintf("\nTurned right\n");
	lock_acquire(AB);
	if(lock_do_i_hold(AB) == 1){
		//kprintf("\nentering\n");
		enter(vehiclenumber, route);
		if(route == 0){ //starting a turning r
			
			leave(vehiclenumber, 0);
		}
		else if(route == 1){ //starting b turning r
			
			leave(vehiclenumber, 1);
		}
		else{ //starting c turning r
			
			leave(vehiclenumber, 2);
		}
	}
	lock_release(AB);
	vehicleCount ++;

	/*
	 * Avoid unused variable warnings.
	 */

	//(void) vehiclenumber;
}


/*
 * vehicle_thread()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long vehiclenumber: holds vehicle id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by stoplight_driver(). Each thread corresponds
 *      to exactly one vehicle. You can fetch information about the vehicle
 *      using its vehiclenumber, plus the get_vehicle_* functions from
 *      stoplight_framework.h.
 *
 *      This function should probably call turn_right() and turn_left(), which
 *      can then each implement their specific turns -- but you are free to
 *      complete this project however you wish.
 */

static
void
vehicle_thread(void * unusedpointer,
		unsigned long vehiclenumber)
{
	/*
	 * Avoid unused variable and function warnings.
	 */
	(void) unusedpointer;
	//(void) vehiclenumber;

	(void) turn_left;
	//(void) turn_right;
	curNum = vehiclenumber;
	int direction = get_vehicle_turn_direction(vehiclenumber);
	int route = get_vehicle_route(vehiclenumber);
	//int type = get_vehicle_type(vehiclenumber);
	approach(vehiclenumber);
	if(direction == 0){
		turn_right(vehiclenumber, route);
	}
	




	/* Note: Throughout this project you will use the get_vehicle_* functions
	 * to get various information about the vehicle. For example:
	 *
	 *     int direction = get_vehicle_turn_direction(vehiclenumber);
	 *     int route = get_vehicle_route(vehiclenumber);
	 *     int type = get_vehicle_type(vehiclenumber);
	 * 
	 * See stoplight_framework.h for documentation on every function, plus various
	 * helpful constants.
	 */
}


/*
 * stoplight_driver()
 *
 * Arguments:
 *      int vehicle_count: The number of vehicles for this problem.
 *                         See the test code in stoplight_framework.c for
 *                         more info.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modify this code as necessary for your solution.
 * 
 *      Be sure that the function remains able to create one thread per vehicle
 *      (a requirement of the project), and also be sure not to delete the call
 *      to finish().
 */

int
stoplight_driver(int vehicle_count)
{
	int index, error;
	vehicleCount = 0;
        AB = lock_create("AB");
	BC = lock_create("BC");
	CA = lock_create("CA");
	completionLock = lock_create("completion_lock");




	for (index = 0; index < vehicle_count; index++) {

		/* This creates a thread for each vehicle, with unique numbers. */
		error = thread_fork("vehicle thread",
				NULL,
				index,
				vehicle_thread,
				NULL
				);

		/*
		 * panic() on error.
		 */

		if (error) {
			panic("approachintersection: thread_fork failed: %s\n",
					strerror(error)
				 );
		}
	}
/**
	while (vehicleCount != vehicle_count) {
		lock_acquire(completionLock);
		if (vehicleCount >= vehicle_count) {
			lock_release(completionLock);
			break;
		}
		lock_release(completionLock);
	}
	
**/
	/* This function indicates the end of the stoplight problem.
	 * This kind of thing is important in a synchronization problem, as
	 * without a specific indicator that the problem has been concluded,
	 * it is impossible to know whether the program has finished successfully
	 * or whether it deadlocked and stopped making progress.
	 * 
	 * Part of your task will be to add synchronization code so that finish()
	 * is not called until every vehicle has made its way through the intersection.
	 * 
	 * Note that deleting the call to finish() will not score you any points. You
	 * must correctly synchronize it to get credit for that part of the project.
	 */
	
	lock_destroy(AB);
	lock_destroy(BC);
	lock_destroy(CA);
	lock_destroy(completionLock);
	finish();

	return 0;
}
