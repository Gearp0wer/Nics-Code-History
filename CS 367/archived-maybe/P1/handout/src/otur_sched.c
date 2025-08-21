/* This is the only file you will be editing.
 * - otur_sched.c (Otur Scheduler Library Code)
 * - Copyright of Starter Code: Prof. Kevin Andrea, George Mason University. All Rights Reserved
 * - Copyright of Student Code: You!  
 * - Copyright of ASCII Art: Modified from Joan Stark (jgs)'s work:
 * -- https://www.asciiart.eu/animals/other-water
 * - Restrictions on Student Code: Do not post your code on any public site (eg. Github).
 * -- Feel free to post your code on a PRIVATE Github and give interviewers access to it.
 * -- You are liable for the protection of your code from others.
 * - Date: Aug 2024
 */

/* CS367 Project 1, Spring Semester, 2024
 * Fill in your Name, GNumber, and Section Number in the following comment fields
 * Name: Nicholas Locklear
 * GNumber: G01090642
 * Section Number: CS367-002  
 */

/* otur CPU Scheduling Library
  .-"""-.
 /      o\
|    o   0).-.
|       .-;(_/         .-.
 \     /  /)).-------._|  `\   ,
  '.  '  /((           `'-./ _/|
    \  .'  )    OTUR    .-.;`  /
     '.                 |  `\-'
       '._            -'    /
 jgs      ``""------`------`
*/
 
/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
/* Unix System Includes */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <sched.h>
/* Local Includes */
#include "otur_sched.h"
#include "vm_support.h"
#include "vm_process.h"

/**
 * TODO:
 * check the return values of all helper func, make sure all return as expected
 * 
 */

/* Feel free to create any helper functions you like! */

unsigned short setBitValue(unsigned short targetNum, int bitPosition, int bitVal) {
    // Check if bitPosition is within valid range (0 to 31 for a 32-bit unsigned int)
    if (bitPosition < 0 || bitPosition > 15) {
        fprintf(stderr, "Invalid bit position\n");
        return targetNum; // Return the original number unchanged
    }
    unsigned short mask = 1u << bitPosition;
    targetNum &= ~mask;
    targetNum |= (bitVal & 1) << bitPosition;

    return targetNum;
}

int is_high(unsigned short targetNum){
  return targetNum >>15;
}
int is_critical(unsigned short targetNum){
  unsigned short mask = 1u<<11;
  return (targetNum & mask)>>11;
}
/**
 * @brief returns a pointer to the last process in the queue; or null if one does not exist.
 * 
 * @param queue a pointer to the queue whos tail you want to return
 * @return a pointer to the last node in the parameter schedule
 */
Otur_process_s *tailFinder(Otur_queue_s *queue){
  Otur_process_s *tail = NULL;
  if(queue->head == NULL){
    return NULL;
  }
  else{
    while(queue->head->next!=NULL){
      tail = queue->head;
      queue->head = queue->head->next;
    }
  }
  return tail;
}
Otur_process_s* nodeHunter(Otur_queue_s *queue, pid_t pid){
  Otur_process_s *terminatedProcess;
  Otur_process_s* currentNode = queue->head;
  Otur_process_s* preNode = queue->head;
  while(currentNode!=NULL){
    if(currentNode->pid == pid){
      terminatedProcess = currentNode;
      preNode->next = currentNode->next;
      currentNode->next = NULL;
      queue->count -=1;
      return terminatedProcess;
    }
    else{
      preNode = currentNode;
      currentNode = currentNode->next;
    }
  }
  return NULL;
}
/**
 * @brief 
 * 
 * @param queue a given singly linked list
 * @param process the item you wish to append to the end of the queue
 * @return 1 if successful, -1 if error
 */
int tailAppend(Otur_queue_s *queue, Otur_process_s *process){
  if(process == NULL){return -1;}
  if(queue->head == NULL){queue->head = process;}
  else{tailFinder(queue)->next = process;}
  queue->tail = process;
  queue->count +=1;
  return 1;
}



Otur_process_s *findHighPriority(Otur_queue_s *queue){
  if(queue->head == NULL){return NULL;}
  Otur_process_s *selectedProcess = NULL;
  Otur_process_s *dummyProcess = NULL;
  Otur_process_s *headIterator = queue->head;

  if(queue->count >0){
    while(selectedProcess == NULL && headIterator->next != NULL){
      if(is_critical(headIterator->state) == 1){
        selectedProcess = headIterator;
        dummyProcess->next = headIterator->next;
        selectedProcess->next = NULL;
      }
      dummyProcess = headIterator; 
      headIterator = headIterator->next;
      queue->count-=1;
    }
    if(selectedProcess == NULL){
      selectedProcess = queue->head;
    } //sets the process to the first node if none are critical
  }
  return selectedProcess;
}

Otur_process_s *findNormalPriority(Otur_queue_s *queue){
  if(queue->head == NULL){return NULL;}
  Otur_process_s *selectedProcess = queue->head;
  queue->head = queue->head->next;
  selectedProcess->next=NULL;
  queue->count-=1;

  return selectedProcess;
}
void freeQueue(Otur_queue_s *queue){
  Otur_process_s* currentNode = queue->head;
  Otur_process_s* preNode = queue->head;
  free(queue->head);
  free(queue->tail);
  while(currentNode!=NULL){
    preNode = currentNode;
    currentNode = currentNode->next;
    free(preNode->cmd);
    free(preNode->next);
    free(preNode);
  }
  free(queue);

}
//=============================================================================================================================

/*** Otur Library API Functions to Complete ***/

/* Initializes the Otur_schedule_s Struct and all of the Otur_queue_s Structs
 * Follow the project documentation for this function.
 * Returns a pointer to the new Otur_schedule_s or NULL on any error.
 * - Hint: What does malloc return on an error?
 */
Otur_schedule_s *otur_initialize() {

  Otur_queue_s* readyQueueHigh = (Otur_queue_s*)malloc(sizeof(Otur_queue_s));
  readyQueueHigh->count = 0;
  readyQueueHigh ->head = NULL;
  readyQueueHigh ->tail = NULL;
  Otur_queue_s* readyQueueNorm = (Otur_queue_s*)malloc(sizeof(Otur_queue_s));
  readyQueueNorm->count = 0;
  readyQueueNorm ->head = NULL;
  readyQueueNorm ->tail = NULL;
  Otur_queue_s* defunctQueue = (Otur_queue_s*)malloc(sizeof(Otur_queue_s));
  defunctQueue->count = 0;
  defunctQueue ->head = NULL;
  defunctQueue ->tail = NULL;

  Otur_schedule_s* scheduleQueue = (Otur_schedule_s*)malloc(sizeof(scheduleQueue));
  scheduleQueue->ready_queue_high = readyQueueHigh;
  scheduleQueue->ready_queue_normal=readyQueueNorm;
  scheduleQueue->defunct_queue=defunctQueue;
      // Check if memory allocation was successful
  if (!readyQueueHigh || !readyQueueNorm || !defunctQueue || !scheduleQueue) {
    return NULL;
  }
  return scheduleQueue; // Replace With Your Code
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Allocate and Initialize a new Otur_process_s with the given information.
 * - Malloc and copy the command string, don't just assign it!
 * Follow the project documentation for this function.
 * - You may assume all arguments are Legal and Correct for this Function Only
 * Returns a pointer to the Otur_process_s on success or a NULL on any error.
 */
Otur_process_s *otur_invoke(pid_t pid, int is_high, int is_critical, char *command) {

  Otur_process_s* processPointer = (Otur_process_s*)malloc(sizeof(Otur_process_s) + sizeof(*command)+101);
  if(!processPointer){return NULL;}
  processPointer->state = 0;
  processPointer->pid = pid;
  processPointer->age = 0;
  if(command !=NULL){
    processPointer->cmd = (char*)malloc(sizeof(command)+1);
    strncpy(processPointer->cmd, command, strlen(command)+1);
  }
  processPointer->next = NULL;
  //unsigned int mask = (1u << 8) - 1;
  if(is_critical == 1){processPointer->state = ((1u<<15) + (1u<<11));} //double check this
  else if(is_critical ==0 && is_high ==1){processPointer->state = (1u<<15);}
  return processPointer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Inserts a process into the appropriate Ready Queue (singly linked lists).
 * Follow the project documentation for this function.
 * - Do not create a new process to insert, insert the SAME process passed in.
 * Returns a 0 on success or a -1 on any error.
 */
int otur_enqueue(Otur_schedule_s *schedule, Otur_process_s *process) {
  if(schedule == NULL || process == NULL){return -1;}

  process->state = setBitValue(process->state,14,0);
  process->state = process->state & (1u<<13);
  process->state = setBitValue(process->state,12,0);
  Otur_process_s *tailPointer = NULL;

  if(is_high(process->state) == 1 || is_critical(process->state) == 1){
    tailPointer = tailFinder(schedule->ready_queue_high);
    if(tailPointer == NULL){schedule->ready_queue_high->head = process;}
    else{tailPointer->next=process;}
    schedule->ready_queue_high->tail = process;
    schedule->ready_queue_high->count +=1;
  }
  else{
    tailPointer = tailFinder(schedule->ready_queue_normal);
    if(tailPointer == NULL){schedule->ready_queue_normal->head = process;}
    else{tailPointer->next=process;}
    schedule->ready_queue_normal->tail = process;
    schedule->ready_queue_normal->count +=1;
  }

  return 0; // Replace With Your Code
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Returns the number of items in a given Otur Queue (singly linked list).
 * Follow the project documentation for this function.
 * Returns the number of processes in the list or -1 on any errors.
 */
int otur_count(Otur_queue_s *queue) {
  return queue->count; 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Selects the best process to run from the Ready Queue (singly linked list).
 * Follow the project documentation for this function.
 * Returns a pointer to the process selected or NULL if none available or on any errors.
 * - Do not create a new process to return, return a pointer to the SAME process selected.
 */
Otur_process_s *otur_select(Otur_schedule_s *schedule) {
  if(schedule == NULL){return NULL;}
  Otur_process_s *selectedNode = NULL;
  if(!(schedule->ready_queue_high == NULL)){
    selectedNode = findHighPriority(schedule->ready_queue_high);
  }
  if(selectedNode == NULL ){
    if(schedule->ready_queue_normal == NULL){return NULL;}
    selectedNode = findNormalPriority(schedule->ready_queue_normal);
  }
  if(selectedNode == NULL){return NULL;}
  selectedNode->age = 0;
  selectedNode->state = 0b1100100011111111 & selectedNode->state; //zeros out the other two state bits
  return selectedNode; 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Ages up all Process nodes in the Ready Queue - Normal and Promotes any that are Starving.
 * - If the Ready Queue - Normal is empty, return 0.  (Nothing to do, so it was a success)
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error.
 */
int otur_promote(Otur_schedule_s *schedule) {
  if(schedule == NULL){return -1;}
  if(schedule->ready_queue_normal == NULL){return 0;}
  else{
    Otur_process_s *dummyHead = schedule->ready_queue_normal->head;
    Otur_process_s *prevNode = NULL;
    while(dummyHead != NULL){
      dummyHead->age +=1;
      dummyHead = dummyHead->next;
    }
    dummyHead = schedule->ready_queue_normal->head;
    while(dummyHead !=NULL){ //if nullpointer, switch to dummy.next
      if(prevNode == NULL){
        if (dummyHead->age >=STARVING_AGE){
          schedule->ready_queue_normal->head = schedule->ready_queue_normal->head->next;
          dummyHead->next=NULL;
          schedule->ready_queue_normal->count -=1;
          if(tailAppend(schedule->ready_queue_high, dummyHead) == -1){return -1;}
        }
      }
      else{
        if (dummyHead->age >=STARVING_AGE){
          prevNode->next=dummyHead->next;
          dummyHead->next = NULL;
          schedule->ready_queue_normal->count -=1;
          if(tailAppend(schedule->ready_queue_high, dummyHead) == -1){return -1;}
        }
      }
      prevNode = dummyHead;
      dummyHead = dummyHead->next;
    }

  }
  return 0; // Replace With Your Code
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* This is called when a process exits normally that was just Running.
 * Put the given node into the Defunct Queue and set the Exit Code into its state
 * - Do not create a new process to insert, insert the SAME process passed in.
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error.
 */
int otur_exited(Otur_schedule_s *schedule, Otur_process_s *process, int exit_code) {
  if(schedule == NULL || process == NULL){return -1;}
  process->state = (process->state & 0b1001100000000000); //and statement to set the high, critical, and defunct bits
  unsigned short processExitCode = (1u<<16) || exit_code;
  process->state = process->state||processExitCode; ///should(?) merge the two together
  int tailreturn = tailAppend(schedule->defunct_queue,process);
  if(tailreturn == 1){
    return 1;
  }
  return -1; 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* This is called when StrawHat kills a process early (kill command). 
 * - The Process will either be in your Ready or Suspended Queue, or neither.
 * - The difference with otur_exited is that this process is in one of your Queues already.
 * Remove the process with matching pid from the Ready or Suspended Queue and add the Exit Code to it.
 * - You have to check both since it could be in either queue.
 * Follow the project documentation for this function.
 * Returns a 0 on success or a -1 on any error (eg. process not found).
 */
int otur_killed(Otur_schedule_s *schedule, pid_t pid, int exit_code) {
  Otur_process_s* terminatedProcess = NULL;
  if(schedule == NULL){return -1;}
  if(schedule->ready_queue_high == NULL && schedule->ready_queue_normal ==NULL){return -1;}
  terminatedProcess = nodeHunter(schedule->ready_queue_high,pid);
  if(terminatedProcess == NULL){
    terminatedProcess = nodeHunter(schedule->ready_queue_normal,pid);
  }
  if(terminatedProcess == NULL){return -1;}
  terminatedProcess->state = (terminatedProcess->state & 0b1001100000000000); //and statement to set the high, critical, and defunct bits
  unsigned short processExitCode = (1u<<16) || exit_code;
  terminatedProcess->state = terminatedProcess->state||processExitCode; ///should(?) merge the two together
  int tailCheck = tailAppend(schedule->defunct_queue,terminatedProcess);
  if(tailCheck ==1){return 0;}
  else{return -1;}
  return -1; // Replace With Your Code
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* This is called when the StrawHat reaps a Defunct process. (reap command)
 * Remove and free the process with matching pid from the Defunct Queue and return its exit code.
 * Follow the project documentation for this function.
 * Returns the process' exit code on success or a -1 if no such process or on any error.
 */
int otur_reap(Otur_schedule_s *schedule, pid_t pid) {
  if(schedule == NULL){
    return -1;
  }
  if(schedule->defunct_queue->head==NULL){
    return 0; //job already done
  }
  Otur_queue_s* defunctQueue = schedule->defunct_queue;
  Otur_process_s* defunctProcess = NULL;
  if(pid == 0){
    defunctProcess = defunctQueue->head;
    defunctQueue->head=defunctQueue->head->next;
    defunctQueue->count-=1;
  }
  else{
    if(defunctQueue->head->pid == pid){
      defunctProcess = defunctQueue->head;
      defunctQueue->head=defunctQueue->head->next;
      defunctProcess->next = NULL;
    }
    else{
      Otur_process_s* dummyProcess = defunctQueue->head;
      Otur_process_s* preProcess = NULL;
      while(dummyProcess != NULL){
        if(dummyProcess->pid == pid){
          if(preProcess == NULL){
            defunctQueue->head=dummyProcess;
            dummyProcess->next = NULL;
            defunctProcess = dummyProcess;
          }
          else{
            preProcess->next = dummyProcess->next;
            dummyProcess->next = NULL;
          }
        defunctQueue->count-=1;
        }
        preProcess = dummyProcess;
        dummyProcess = dummyProcess->next;
      }
    }

  }

  defunctQueue->tail = tailFinder(defunctQueue); //cant be assed to actually check if the tail is right, so ill just re set it.
  free(defunctProcess->cmd);
  free(defunctProcess->next);
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Frees all allocated memory in the Otur_schedule_s, all of the Queues, and all of their Nodes.
 * Follow the project documentation for this function.
 * Returns void.
 */
void otur_cleanup(Otur_schedule_s *schedule) {
  freeQueue(schedule->defunct_queue);
  freeQueue(schedule->ready_queue_high);
  freeQueue(schedule->ready_queue_normal);
  free(schedule);

}
