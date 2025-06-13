/* FEEL FREE TO EDIT THIS FILE
 * - test_schedule.c (Trilby VM)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// Local Includes
#include "vm_support.h" // Gives abort_error, print_warning, print_status, print_debug commands
#include "op_sched.h" // Your header for the functions you're testing.

int debug_mode = 1; // Hardcodes debug on for the custom print functions

/* This is an EXAMPLE tester file, change anything you like!
 * - This shows an example by testing op_create.
 * - To make this useful, modify this function or create others for the rest of the
 *   functions that you want to test from your code.
 */


// Local Prototypes
void test_op_create();

int main() {
  // print_status is a helper function to print a message when you run the code.
  // These helper functions only print if debug_mode is 1
  print_status("Test 1: Testing OP Create");
  // Call this local function to test your op_create code.
  test_op_create();

  return 0;
}

// Local function to test schedule_create from op_sched.c
void test_op_create() {
  /* print_debug, print_status, print_warning, print_error, and abort_error are all 
   *   helper functions that we wrote to print messages to the screen during debugging.
   * - Feel free to use these, or not, based on your own preferences.
   * BTW: gdb works muuuuuch better in this test file than it does in vm
   */
  print_debug("...Calling op_create()");

  /* Note: MARK is a really cool helper.  Unlike the others, it works just like printf.
   * It also prints out the file, function, and line number that it was called from.
   * You can use it to check values throuhgout the code and mark where you printed from.
   * BTW: gdb also does this much better too.
   */
  MARK("I can be used anywhere, even if debug mode is off.\n");
  MARK("I work just like printf! %s %d %lf\n", "Cool!", 42, 3.14);
  // Call the function I want to test.
  Op_schedule_s *header = op_create();
  
  // Now that we called it and got the pointer to the header, let's test to see if we did it right!
  if(header == NULL) {
    abort_error("...op_create returned NULL!", __FILE__);
  }
  if(header->ready_queue_high == NULL || header->ready_queue_low == NULL || header->defunct_queue == NULL) {
    abort_error("...op_create returned at least one NULL queue.", __FILE__);
  }
  if(header->ready_queue_high->count != 0) {
    print_warning("...The count on Ready Queue High is not 0!");
  }
  // ... and this would continue checking all the things that need to be done.

  // Last example code, how to print the schedule of all three linked lists.
  print_status("...Printing the Schedule");
  print_op_debug(header);
  print_status("...op_create is looking good so far.");
}
