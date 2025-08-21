/* FEEL FREE TO EDIT THIS FILE
 * - test_otur_sched.c (Otur Scheduler Library Code)
 * - Copyright of Starter Code: Prof. Kevin Andrea, George Mason University.  All Rights Reserved
 * - Copyright of Student Code: You!
 * - Date: Jan 2024
 *
 *   Framework to demonstrate how you can write a Unit Tester for your Project
 *   - Not a requirement to use, but it may be helpful if you like.
 *   - This only has one example of a test case in it, so it is just to show how to write them.
 *
 *   This lets you test your otur_sched.c code WITHOUT any of the StrawHat code running.
 *
 *   Why run all tests every time instead of checking a function once to see that it works?
 *   - You could break existing code when adding a new feature.
 *   - Test files like this are useful to check all of the tests every time, so you can make sure
 *     you didn't break something that used to work when you add new code.
 */

/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
/* Local Includes */
#include "otur_sched.h" // Your schedule for the functions you're testing.
#include "vm_support.h" // Gives ABORT_ERROR, PRINT_WARNING, PRINT_STATUS, PRINT_DEBUG commands

/* Globals (static means it's private to this file only) */
int g_debug_mode = 1; // Hardcodes debug on for the custom print functions
 
/* Local Prototypes */
void test_otur_initialize();
static void test_queue_initialized(Otur_queue_s *queue);

/* This is an EXAMPLE tester file, change anything you like!
 * - This shows an example by testing otur_initialize.
 * - To make this useful, modify this function or create others for the rest of the
 *   functions that you want to test from your code.
 */
int main() {
  g_debug_mode = 1;  // These helper functions only print if g_debug_mode is 1

  // Here I'm Calling a local helper function to test your otur_initialize code.
  // - You can make any helper functions you like to test it however you want!
  
  // PRINT_STATUS is a helper macro to print a message when you run the code.
  // - The definitions are in int/_support.h
  // - It works just like printf, but it prints out in some nice colors.
  // - It also adds a newline at the end, so you don't need to here.
  // - The PRINT_* macros are available for your otur_sched.c as well, if you want to use them.
  PRINT_STATUS("Test 1: Testing otur_initialize");
  test_otur_initialize();

  // You would add more calls to testing helper functions that you like.
  // Then when done, you can print a nice message an then return.
  PRINT_STATUS("All tests complete!");
  return 0;
}

/* Local function to test schedule_initialize from otur_sched.c */
void test_otur_initialize() {
  /* PRINT_DEBUG, PRINT_STATUS, PRINT_WARNING, PRINT_ERROR, and ABORT_ERROR are all 
   *   helper macros that we wrote to print messages to the screen during debugging.
   * - Feel free to use these, or not, based on your own preferences.
   * - These work just like printf, but print different labels and they add in a newline at the end.
   * BTW: gdb works muuuuuch better in this test file than it does in 
   */
  PRINT_DEBUG("...Calling otur_initialize()");

  /* Note: MARK is a really cool helper macro.  Like the others, it works just like printf.
   * It also prints out the file, function, and line number that it was called from.
   * You can use it to check values throuhgout the code and mark where you printed from.
   * BTW: gdb also does this much better too.
   */
  MARK("I can be used anywhere, even if debug mode is off.\n");
  MARK("I work just like printf! %s %d %lf\n", "Cool!", 42, 3.14);

  // Begin Testing
  // - You can just call the function you want to test with any arguments needed.
  // - You may need to set up some arguments first, depending on what you want to test.
  Otur_schedule_s *schedule = otur_initialize();
  
  // Now that we called it and got the pointer to the schedule, let's test to see if we did it right!
  if(schedule == NULL) {
    // ABORT_ERROR will kill the program when it hits, which is good if you hit a bug.
    ABORT_ERROR("...otur_initialize returned NULL!"); 
  }
  // Header is good, so let's test the queues to see if they're all initialized properly.
  PRINT_STATUS("...Checking the Ready Queue - High");
  test_queue_initialized(schedule->ready_queue_high); // This is another helper function I wrote in this file.
  PRINT_STATUS("...Checking the Ready Queue - Normal");
  test_queue_initialized(schedule->ready_queue_normal); // This is another helper function I wrote in this file.
  PRINT_STATUS("...Checking the Defunct Queue");
  test_queue_initialized(schedule->defunct_queue); // This is another helper function I wrote in this file.

  // Last example code, how to print the schedule of all three linked lists.
  PRINT_STATUS("...Printing the Schedule");
  // You can use print_otur_debug to print out all of the schedules.
  // - Note: the second argument is for the Process on the CPU
  //         When testing, if you select a process, you can pass a pointer to that into the
  //           second argument to have it print out nice.
  // - In this case, we haven't selected any Process, so passing in NULL
  print_otur_debug(schedule, NULL); // the second argument here is used for the process on the CPU.
  PRINT_STATUS("...otur_initialize is looking good so far.");
}

/* Helper function to test if a queue is properly initialized
 * Exits the program with ABORT_ERROR on any failures.
 */
static void test_queue_initialized(Otur_queue_s *queue) {
  // Always test a pointer before dereferencing it!
  if(queue == NULL) {
    ABORT_ERROR("...tried to test a NULL queue!");
  }

  // Check that the head pointer is NULL.
  if(queue->head != NULL) {
    ABORT_ERROR("...the Queue doesn't have a NULL head pointer!");
  }
  // Check that the count is 0.
  if(queue->count != 0) {
    ABORT_ERROR("...the Queue's count is not initialized to 0!");
  }
}
