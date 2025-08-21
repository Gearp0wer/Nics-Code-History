/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name: Nicholas Locklear 
 * GNumber: G01090642
 * 
 * add base shell func
 *  list
 *  purge TASK
 * 
 * Spend some time designing the overall layout on paper before starting to code. 
 * Once you have this in your design, add the various features in an order which lets you ensure that your code works.
 */

#include <sys/wait.h>
#include "logging.h"
#include "anav.h"
#include "parse.h"
#include "util.h"

/* Constants */
#define DEBUG 1 /* You can set this to 0 to turn off the debug parse information */
#define STOP_SHELL  0
#define RUN_SHELL   1

//---------------------------------------------------------------------------------------------------------

typedef struct TaskStruct {
   int PID;
   int State;
   int Tasknum;
   int ExitCode;
   char* cmd;
   char** argv;
   Instruction *Task;
	
   struct TaskStruct *next; 
   struct TaskStruct *prev;
}node;

node *Head = NULL; //highest tasknum
node *Tail= NULL; //lowest tasknum
int HighestTask = 0;

//---------------------------------------------------------------------------------------------------------

//is list empty
bool isEmpty() {
   return (Head == NULL);
}

int length() {
  int length = 0;
  node* current = Head;
  //printf("length check 1\n");
  if (isEmpty() == false){
    for(current = Head; current != NULL; current = current->next){
      //printf("length: %d\t", length);
      //printf("Tasknum: %d\n", current->Tasknum);
      length++;
    }
  }
  else{
    return 0;
  }
  
  //printf("length check 2\n");
  return length;
}
  
int nodeInit(node *TaskStruct){
  if (!TaskStruct ){ return 0;}
  TaskStruct->State = 0;
  TaskStruct->PID = 0;
  TaskStruct->Tasknum = 0;
  TaskStruct->ExitCode = 0;

  TaskStruct->Task = NULL;
  TaskStruct->next = NULL;
  TaskStruct->prev = NULL;
  return 1;
}
node* Getnode(int TaskNum){
  node *current = Head;
  for(current = Head; current != NULL; current = current->next){
    if(current->Tasknum == TaskNum){
      return current;
    }
  }
  return current;  //check proper handling
}


//---------------------------------------------------------------------------------------------------------

int NewTask(char *cmd, char **argv){
  if(!cmd || !argv){
    //printf("excuse you, why are you here?\n");
    return 0;
  }
  node *Newnode = (node*)malloc(sizeof(node));

  Instruction *Task = (Instruction*)malloc(sizeof(Instruction)+100);
  //check if null and go to sig

  //printf("input check 1\n");
  parse(cmd,Task,argv); //shouldnt need to alloc?

  nodeInit(Newnode);
  //printf("Newtask: %s\n", cmd);
  Newnode->Task = Task;
  Newnode->cmd = string_copy(cmd);
  Newnode->argv = argv;

  Newnode->Tasknum = HighestTask + 1;
  HighestTask += 1;
  //printf("input check 4: %d\t", Newnode->Tasknum);
  //printf("input check 4.1: %s\n", Newnode->cmd);
  if( isEmpty()){
    Head = Newnode;
    Tail = Newnode;
    //printf("input check 4.2: %d\n", Head->Tasknum);
  }else{ // feed in normally?
    //node *prev_node = findPrevnode(Head, Newnode); //what if its null?
    //insertnode(Head, Newnode, prev_node);
    Newnode->next = Head;
    Head->prev = Newnode;
    Head = Head->prev;
    //printf("input check 4.7: %d\n", Newnode->Tasknum);

  }
  //printf("input check 5\n");

  log_anav_task_init(Newnode->Tasknum,cmd); //logs creation
  return 1;
  //return 1 on success, 0 on failure
}
int NodeFree(node *input){ // use to free the atributes of the struct before freeing the struct
   if(!input){return 0;}
//   free(input->PID);
//   input->PID = NULL;
//   free(input->State);
//   input->State = NULL;
//   free(input->Tasknum);
//   input->Tasknum = NULL;
//   free(input->ExitCode);
//   input->ExitCode = NULL;
    
   free_instruction(input->Task);
   free(input->cmd);
   input->Task = NULL;
	
   input->next = NULL; 
   input->prev = NULL;
   //free(input);
   return 1;
}

  int RemoveTask(int Tasknum){ //more error checking needed
    //sanity check
    int Length = length();
    if(Length == 0|| Tasknum <1 || Tasknum > HighestTask){
      //printf("check: 0\n");
      return 0;
    } 
    node *current = Head;
    //printf("check: 1\n");
    if(Tasknum == HighestTask && Length > 1){
      HighestTask = Head->next->Tasknum;
      //printf("Head Tasknum: %d\n", HighestTask);
      Head = Head->next;
      //printf("check: Head tasknum: %d\n", Head->Tasknum);
      NodeFree(current);
      //printf("check: 1.1\n"); 
      //free(Head);
      //printf("check: 1.12\n"); 
      //printf("check: Head tasknum: %d\n", Head->Tasknum);
      return 1;
    }
    else if(Tasknum == HighestTask && Length == 1){
      HighestTask = 0;
      Tail = NULL;
      free_instruction(current->Task);
      NodeFree(current);
      Head = NULL;
      //printf("check: 1.2\n");
      return 1;
    }
    for(int i = HighestTask; i > 0; i=current->Tasknum){
      //printf("Tasknum: %d\t", current->Tasknum);
      if(i==Tasknum){
        //printf("Found\n");
        if(current->next == NULL){ //at the end
          current->prev->next = NULL;
          Tail = current->prev;
          //printf("check: END\n");
        }
        else{
          current->prev->next = current->next;
          current->next->prev = current->prev;
          //printf("check: sectioned out\n");
        }
        free_instruction(current->Task);
        //printf("check: remove attempt\n");
        NodeFree(current);
        //printf("check: removed\n");
        return 1;
      }
      current = current->next;
    }
    return 1;
  }

int ListTask(char *cmd){
  //int Length = 
  //printf("list check 1\n");
  int num_tasks = length();
  log_anav_num_tasks(length());
  //printf("list check 2: %d\n", num_tasks);
  node *current = Tail;
  for(int i = 0; i < num_tasks; i++){
    log_anav_task_info(current->Tasknum, current->State, current->ExitCode, current->PID, current->cmd);
    current = current->prev;
  }
  //printf("list check 3\n");

  return 1;//check proper handling
}

int KillTask(int Tasknum){
  /**
   *  If the selected task does not exist, call log_anav_task_num_error(task_num).
   * � If the task is currently idle, call log_anav_status_error(task_num, status) instead.
   *  o An idle task is a Ready, Finished or Killed task; do not kill such a task.
   * � When signaling the kill, call log_anav_sig_sent(LOG_CMD_KILL, task_num,
   * 
   */
    node* current = Head;
    if(Tasknum == HighestTask){
      HighestTask = Head->next->Tasknum;
    }
    while (current != NULL && current->Tasknum != Tasknum) {
        current = current->next;
    }
    if (current == NULL) {
        // Node not found in list 
        return 0; //throws error
    }
    else if(current->State != 1 && current->State != 2){//Node not killable
      log_anav_status_error(Tasknum, current->State);
      return 1;
    }
    //sig here
  return 1; //check proper handling
}

int SuspendTask(int Tasknum){
  /**
   *  If the selected task does not exist, call log_anav_task_num_error(task_num).
   * � If the task is currently idle, call log_anav_status_error(task_num, status) instead.
   *  o An idle task is a Ready, Finished or Killed task; do not kill such a task.
   * � When signaling the kill, call log_anav_sig_sent(LOG_CMD_KILL, task_num,
   * 
   */
    node* current = Head;
    if(Tasknum == HighestTask){
      HighestTask = Head->next->Tasknum;
    }
    while (current != NULL && current->Tasknum != Tasknum) {
        current = current->next;
    }
    if (current == NULL) {
        // Node not found in list 
        return 0; //throws error
    }
    else if(current->State != 1 && current->State != 2){//Node not killable
      log_anav_status_error(Tasknum, current->State);
      return 1;
    }
    log_anav_sig_sent(LOG_CMD_SUSPEND, Tasknum, current->PID);
    //take off ready queue, move to suspended
    return 1; //check proper handling
}


int exec(char *cmd, int task_num, char* in, char* out, char **argv){
  int Length = length();
  if(Length == 0|| task_num <1 || task_num > HighestTask){
    log_anav_task_num_error(task_num);
    return 1;
  }
  node *tasktoExec = Getnode(task_num);
  //int execNum = tasktoExec->Tasknum;
  if(tasktoExec->Tasknum != task_num){
    log_anav_task_num_error(task_num);
    return 1;
  }
  char *argvNew[MAXARGS+1] = {0};
  char *p_tok = NULL;
  char buffer[MAXLINE] = {0};
  strncpy(buffer, tasktoExec->cmd, MAXLINE);

  p_tok = strtok(buffer, " ");
  if (p_tok == NULL) { return 0; }

  int index = 0;

  // copy the tokens into argv
  while(p_tok != NULL) {
      argvNew[index] = string_copy(p_tok);

    index++;
      p_tok = strtok(NULL, " ");
  if (index >=26) p_tok = NULL;}
  argvNew[index] = 0;



  if(tasktoExec->State == 1 || tasktoExec->State == 2){
    log_anav_status_error(task_num, (tasktoExec->State == 1) ? LOG_STATE_RUNNING : LOG_STATE_SUSPENDED); //log error of running, else error of suspended
  }
  int Forked = fork();
  tasktoExec->PID = getpid();
  
  if (Forked != 0){
    log_anav_status_change(task_num, tasktoExec->PID, LOG_FG, tasktoExec->cmd, LOG_START);
  //  printf("check: 1.1\n");
    wait(NULL);
    tasktoExec->ExitCode = 0;
    tasktoExec->State = 3;
    log_anav_status_change(task_num, tasktoExec->PID, LOG_FG, tasktoExec->cmd, LOG_TERM );
    	
  }
  else{

//    printf("check: 1.2\n");
    char path[50]  = "./";
    strcat(path,argvNew[0]);
    if(execv(path,argvNew) < 0){
      char path2[50]  = "/usr/bin/";
      strcat(path2,argvNew[0]);

      if (execv(path2, argvNew) < 0){
        log_anav_exec_error(tasktoExec->cmd);
  //      printf("check: 1.5\n");
        tasktoExec->ExitCode = 1;
        exit(1);
      }
      else{
        //signal(SIGINT, handler);
        exit(0);
      }
    }
    else{
      //signal(SIGINT, handler);
      exit(0);
    }
//    printf("check: 1.7\n");  
  }
//  printf("check: 1.8\n");
  return 1;
}


int BG(char *cmd, int task_num, char* in, char* out, char **argv){
  int Length = length();
  if(Length == 0|| task_num <1 || task_num > HighestTask){
    log_anav_task_num_error(task_num);
    return 1;
  }
  node *tasktoExec = Getnode(task_num);
  //int execNum = tasktoExec->Tasknum;
  if(tasktoExec->Tasknum != task_num){
    log_anav_task_num_error(task_num);
    return 1;
  }
  char *argvNew[MAXARGS+2] = {0};
  char *p_tok = NULL;
  char buffer[MAXLINE] = {0};
  strncpy(buffer, tasktoExec->cmd, MAXLINE);

  p_tok = strtok(buffer, " ");
  if (p_tok == NULL) { return 0; }

  int index = 0;

  // copy the tokens into argv
  while(p_tok != NULL) {
      argvNew[index] = string_copy(p_tok);

    index++;
      p_tok = strtok(NULL, " ");
  if (index >=26) p_tok = NULL;} 
  argvNew[index] = 0;
  argvNew[index + 1] = "&";


  if(tasktoExec->State == 1 || tasktoExec->State == 2){
    log_anav_status_error(task_num, (tasktoExec->State == 1) ? LOG_STATE_RUNNING : LOG_STATE_SUSPENDED); //log error of running, else error of suspended
  }
  int Forked = fork();
  tasktoExec->PID = getpid();
  
  if (Forked != 0){
    log_anav_status_change(task_num, tasktoExec->PID, LOG_BG, tasktoExec->cmd, LOG_START);
  //  printf("check: 1.1\n");
    wait(NULL);
    tasktoExec->ExitCode = 0;
    tasktoExec->State = 3;
    log_anav_status_change(task_num, tasktoExec->PID, LOG_BG, tasktoExec->cmd, LOG_TERM );
    	
  }
  else{

//    printf("check: 1.2\n");
    char path[50]  = "./";
    strcat(path,argvNew[0]);
    if(execv(path,argvNew) < 0){
      char path2[50]  = "/usr/bin/";
      strcat(path2,argvNew[0]);

      if (execv(path2, argvNew) < 0){
        log_anav_exec_error(tasktoExec->cmd);
  //      printf("check: 1.5\n");
        tasktoExec->ExitCode = 1;
        exit(1);
      }
      else{
        //signal(SIGINT, handler);
        exit(0);
      }
    }
    else{
      //signal(SIGINT, handler);
      exit(0);
    }
//    printf("check: 1.7\n");  
  }
//  printf("check: 1.8\n");
  return 1;
}


//---------------------------------------------------------------------------------------------------------

/* The entry of your text processor program */
int main() {
  char *cmd = NULL;
  int do_run_shell = RUN_SHELL;

  /* Intial Prompt and Welcome */
  log_anav_intro();
  log_anav_help();

  /* Shell looping here to accept user command and execute */
  while (do_run_shell == RUN_SHELL) {
    char *argv[MAXARGS+1] = {0};  /* Argument list */
    Instruction inst = {0};       /* Instruction structure: check parse.h */

    /* Print prompt */
    log_anav_prompt();

    /* Get Input - Allocates memory for the cmd copy */
    cmd = get_input(); 
    /* If the input is whitespace/invalid, get new input from the user. */
    if(cmd == NULL) {
      continue;
    }

    /* Check to see if this is the quit built-in */
    if(strncmp(cmd, "quit", 4) == 0) {
      /* This is a match, so we'll set the main loop to exit when you finish processing it */
      do_run_shell = STOP_SHELL;
      /* Note: You will need to print a message when quit is entered, 
       *       you can do it here, in your functions, or at the end of main.
       */
    }

    /* Parse the Command and Populate the Instruction and Arguments */
    initialize_command(&inst, argv);    /* initialize arg lists and instruction */
    parse(cmd, &inst, argv);            /* call provided parse() */

    if (DEBUG) {  /* display parse result, redefine DEBUG to turn it off */
      debug_print_parse(cmd, &inst, argv, "main (after parse)");
    }

    /*.===============================================.
     *| Add your code below this line to continue. 
     *| - The command has been parsed and you have cmd, inst, and argv filled with data.
     *| - Very highly recommended to start calling your own functions after this point.
     *o===============================================*/

    Instruction *Task = (Instruction*)malloc(sizeof(Instruction)+100);
    char *argvCopy[MAXARGS+1] = {0};
    parse(cmd,Task,argvCopy);
    int returncode;
    //printf("argv check1: %s\n", argvCopy[0]);

    if(strncmp(cmd, "purge", 5) == 0){ 
      returncode = (RemoveTask(Task->id1));
      if(returncode == 0){
        log_anav_task_num_error(Task->id1);
        continue;
      }
      else{
        log_anav_purge(Task->id1);
      }
    }
    else if(strncmp(cmd, "kill", 4) == 0){
      returncode = KillTask(Task->id1);
      if(returncode == 0){
        log_anav_task_num_error(Task->id1);
        continue;
      }
    }
    else if(strncmp(cmd, "suspend", 7) == 0){
      returncode = SuspendTask(Task->id1);
      if(returncode == 0){
        log_anav_task_num_error(Task->id1);
        continue;
      }
    }
    else if(strncmp(cmd, "exec", 4) == 0){
      exec(cmd, Task->id1, Task->infile, Task->outfile, clone_argv(argv));
      continue;
    }
    else if(strncmp(cmd, "bg", 2) == 0){
      BG(cmd, Task->id1, Task->infile, Task->outfile, clone_argv(argv));
      continue;
    }
    else if(strncmp(cmd, "help", 4) == 0){
      //printf("help\n");
      log_anav_help();
    }
    else if(strncmp(cmd, "list", 4) == 0){
      //printf("list\n");
      ListTask(cmd);
    }
    else if(strncmp(cmd, "quit", 4) == 0){
      log_anav_quit();
      continue;
    }
    else{
      //printf("Newtask: %s\n", cmd); // copy all info, create new struct, populate double ll
      NewTask(cmd, clone_argv(argv)); //copy in argv and cmd const w utils.c, figure out when to free?
    }

    free_instruction(Task);  


  

    /*.===============================================.
     *| After your code: We cleanup before Looping to the next command.
     *| free_command WILL free the cmd, inst and argv data.
     *| Make sure you've copied any needed information to your Task first.
     *| Hint: You can use the util.c functions for copying this information.
     *o===============================================*/
    free_command(cmd, &inst, argv);
    cmd = NULL;
  }

  return 0;
}
