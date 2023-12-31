/* This is the only file you will be editing.
 * - Copyright of Starter Code: Prof. Kevin Andrea, George Mason University.  All Rights Reserved
 * - Copyright of Student Code: You!  
 * - Restrictions on Student Code: Do not post your code on any public site (eg. Github).
 * -- Feel free to post your code on a PRIVATE Github and give interviewers access to it.
 * -- You are liable for the protection of your code from others.
 * - Date: Jan 2023
 */

/* Fill in your Name and GNumber in the following two comment fields
 * Name: Nicholas Locklear
 * GNumber: G01090642
 * TODO
 * establish the vm running an output correctly
 */

// System Includes
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <sched.h>
// Local Includes
#include "op_sched.h"
#include "vm_support.h"
#include "vm_process.h"

// Feel free to use these in your code, if you like! 
#define CRITICAL_FLAG   (1 << 31) 
#define LOW_FLAG        (1 << 30) 
#define READY_FLAG      (1 << 29)
#define DEFUNCT_FLAG    (1 << 28)

/* Feel free to create any helper functions you like! */

/* Initializes the Op_schedule_s Struct and all of the Op_queue_s Structs
 * Follow the project documentation for this function.
 * Returns a pointer to the new Op_schedule_s or NULL on any error.
 */
Op_schedule_s *op_create() {
  Op_schedule_s *new_op_schedule = (Op_schedule_s *)malloc(sizeof(Op_schedule_s));
  if (new_op_schedule == NULL) {
    return NULL;
  }
  new_op_schedule->ready_queue_high = (Op_queue_s *)malloc(sizeof(Op_queue_s));
  new_op_schedule->ready_queue_low = (Op_queue_s *)malloc(sizeof(Op_queue_s));
  new_op_schedule->defunct_queue = (Op_queue_s *)malloc(sizeof(Op_queue_s));
  new_op_schedule->ready_queue_high->count = 0;
  new_op_schedule->ready_queue_high->head = NULL;
  new_op_schedule->ready_queue_low->count = 0;
  new_op_schedule->ready_queue_low->head = NULL;
  new_op_schedule->defunct_queue->count = 0;
  new_op_schedule->defunct_queue->head = NULL;
  return new_op_schedule;
}

/* Create a new Op_process_s with the given information.
 * - Malloc and copy the command string, don't just assign it!
 * Follow the project documentation for this function.
 * Returns the Op_process_s on success or a NULL on any error.
 */

Op_process_s *op_new_process(char *command, pid_t pid, int is_low, int is_critical) {
  Op_process_s *new_process = (Op_process_s *)malloc(sizeof(process_data_t));
  if (!new_process) {
    return NULL; // return NULL on error
  }
  // Initialize the state member (todo: figure out what state members are)
  new_process->state = READY_FLAG;
  if (is_low) {
    new_process->state |= LOW_FLAG;
  }
  if (is_critical) {
    new_process->state |= CRITICAL_FLAG;
  }
  // Initialize other members
  // return NULL on error 
  new_process->age = 0;
  new_process->pid = pid;
  new_process->cmd = (char *)malloc(strlen(command) + 1);
  if (!new_process->cmd) {
    free(new_process);
    return NULL; 
  }
  strncpy(new_process->cmd, command, strlen(command) + 1);
  new_process->next = NULL;
  return new_process;
}

/* Adds a process into the appropriate singly linked list queue.
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error.
 */
int op_add(Op_schedule_s *schedule, Op_process_s *process) {
  if (!schedule || !process){
    MARK("error encountered\n");
    return -1; // Check for NULL
  } 

  // Set the state member to the ready state
  process->state &= ~DEFUNCT_FLAG; // Clear defunct
  process->state |= READY_FLAG; // Set ready
  // Add the Process Node to the end of the appropriate Ready Queue
  // if the process is equal to the low flag, set into low queue. else, set in high queue
  Op_queue_s *queue;
  if(process->state & LOW_FLAG){
      queue = schedule->ready_queue_low;
  }
  else{
    schedule->ready_queue_high;
  }

  if (!queue->head) {
    // If the head pointer is NULL, this will be the first process
    MARK("head set\n");
    queue->count += 1;
    queue->head = process;
  } 
  else {
    Op_process_s *current = queue->head;
    while (current->next) {
      current = current->next;
    }
    current->next = process;
    queue->count += 1;
  }
  return 0;
}

/* Returns the number of items in a given Op_queue_s
 * Follow the project documentation for this function.
 * Returns the number of processes in the list or -1 on any errors.
 */
int op_get_count(Op_queue_s *queue) {
  if(queue->count < 0 || queue == NULL){
    return -1;
  }
  return queue->count;
}

/* Selects the next process to run from the High Ready Queue.
 * Follow the project documentation for this function.
 * Returns the process selected or NULL if none available or on any errors.
 */
Op_process_s *op_select_high(Op_schedule_s *schedule) {
  if(!schedule->ready_queue_high->head){ //check for null
    return NULL;
  }
  Op_process_s *HighQueueHead = schedule->ready_queue_high->head; //get a pointer to the head
  if (HighQueueHead->state & CRITICAL_FLAG){ //check if flag = state
    schedule->ready_queue_high->head = schedule->ready_queue_high->head->next;
    HighQueueHead->age = 0;
    HighQueueHead->next = NULL;
    schedule->ready_queue_high->count -= 1;
    return HighQueueHead;
  }
  else{ //use pointer from head, iterate to find first critical
    Op_process_s *current = schedule->ready_queue_high->head;
    Op_process_s *previous = NULL;
    while (current->next) {
      if (current->state & CRITICAL_FLAG){
        HighQueueHead = current;
        HighQueueHead->age = 0;
        previous->next = current->next;
        HighQueueHead->next = NULL;
        schedule->ready_queue_high->count -= 1;
        break;
        }
      else{
        previous = current;
        current = current->next;
        }
    }
    current = schedule->ready_queue_high->head;
  }
  return HighQueueHead; // Replace This Line with Your Code!
}

/* Schedule the next process to run from the Low Ready Queue.
 * Follow the project documentation for this function.
 * Returns the process selected or NULL if none available or on any errors.
 */
Op_process_s *op_select_low(Op_schedule_s *schedule) {
  Op_process_s *LowQueueHead = schedule->ready_queue_low->head; //get a pointer to the head
  if(!schedule->ready_queue_low->head){ //check for null
    return NULL;
  }
  else{
    *schedule->ready_queue_low->head = schedule->ready_queue_low->head->next;
    LowQueueHead->age = 0;
    LowQueueHead->next = NULL;
  }
  return LowQueueHead; // Replace This Line with Your Code!
}

/* Add age to all processes in the Ready - Low Priority Queue, then
 *  promote all processes that are >= MAX_AGE.
 * Follow the project documentation for this function.
 * Returns a 0 on success or -1 on any errors.
 */
int op_promote_processes(Op_schedule_s *schedule) {
  Op_process_s *curr_lowHead = schedule->ready_queue_low->head;
  Op_process_s *prev_low = NULL;
  Op_process_s *last_high = NULL;
  if(!schedule || !schedule->ready_queue_low->head){
    return -1;
  }
  while (curr_lowHead != NULL){// Increment age
    curr_lowHead->age += 1;
    if (curr_lowHead->age >= MAX_AGE) {//promote the process to high priority queue if age >= max
      Op_process_s *promote = curr_lowHead;
      promote->age = 0;
      promote->next = NULL;
      if (prev_low == NULL){
        schedule->ready_queue_low->head = curr_lowHead->next;
      } 
      else{
        prev_low->next = curr_lowHead->next;
      }
      curr_lowHead = curr_lowHead->next;  
      schedule->ready_queue_low->count -=1;
      schedule->ready_queue_high->count +=1;
      if (schedule->ready_queue_high->head == NULL){// Add the promoted process to the end of the Ready Queue
        schedule->ready_queue_high->head = promote;
      } 
      else{
        last_high->next = promote;
      }
      last_high = promote;
    } 
    else{
      prev_low = curr_lowHead;
      curr_lowHead = curr_lowHead->next;
    }
  }
  return 0;
}

/* This is called when a process exits normally.
 * Put the given node into the Defunct Queue and set the Exit Code 
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error.
 */
int op_exited(Op_schedule_s *schedule, Op_process_s *process, int exit_code) {
  // Set the state member of the process to the defunct state + bits used for exit
  process->state = (process->state & (CRITICAL_FLAG | LOW_FLAG)) | DEFUNCT_FLAG;
  process->state = (process->state & ~0x0FFFFFFF) | (exit_code & 0x0FFFFFFF);
  // Insert the process to the end of the defunct queue
  if (schedule->defunct_queue->head == NULL){
    schedule->defunct_queue->head = process;  // Insert as head is queue empty
    process->next = NULL;
  } 
  else{
    Op_process_s *current = schedule->defunct_queue->head;// If the queue is not empty, insert at end
    while (current->next != NULL){
      current = current->next;
    }
    current->next = process;
    process->next = NULL;
  }
  return 0;
}

/* This is called when the OS terminates a process early.
 * Remove the process with matching pid from Ready High or Ready Low and add the Exit Code to it.
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error.
 */

int op_terminated(Op_schedule_s *schedule, pid_t pid, int exit_code) {
  Op_process_s *curr, *prev;
  int found = 0;

  // Search the high priority queue
  curr = schedule->ready_queue_high->head;
  prev = NULL;
  while (curr) {
    if (curr->pid == pid) {
      found = 1;
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  if (!found) {
    // Search the low priority queue
    curr = schedule->ready_queue_low->head;
    prev = NULL;
    while (curr) {
      if (curr->pid == pid) {
        found = 1;
        break;
      }
      prev = curr;
      curr = curr->next;
    }
  }

  if (!found) {
    return -1;
  }

  // Remove the process from the queue
  if (prev) {
    prev->next = curr->next;
  } else {
    if (curr == schedule->ready_queue_high->head) {
      schedule->ready_queue_high->head = curr->next;
    } else if (curr == schedule->ready_queue_low->head) {
      schedule->ready_queue_low->head = curr->next;
    }
  }

  // Set the state of the process to DEFUNCT_FLAG
  curr->state &= ~(READY_FLAG);
  curr->state |= DEFUNCT_FLAG;

  // Set the exit code
  curr->state &= 0xF0000000;
  curr->state |= (exit_code & 0x0FFFFFFF);

  // Insert the process into the defunct queue
  if (!schedule->defunct_queue->head) {
    schedule->defunct_queue->head = curr;
    curr->next = NULL;
  } else {
    Op_process_s *temp = schedule->defunct_queue->head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = curr;
    curr->next = NULL;
  }

  return 0;
}


/* Frees all allocated memory in the Op_schedule_s, all of the Queues, and all of their Nodes.
 * Follow the project documentation for this function.
 */
void op_deallocate(Op_schedule_s *schedule) {
  Op_queue_s *queues[] = {schedule->ready_queue_high, schedule->ready_queue_low, schedule->defunct_queue};
  int i;
  for (i = 0; i < 3; i++) {
    Op_queue_s *queue = queues[i];
    if (queue != NULL) {
      Op_process_s *curr = queue->head;
      while (curr != NULL) {
        Op_process_s *next = curr->next;
        free(curr->cmd);
        free(curr);
        curr = next;
      }
      free(queue);
    }
  }
  free(schedule);
}
