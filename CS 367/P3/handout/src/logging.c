/* Do Not Modify This File */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "logging.h"

#define BUFSIZE 255

#define anav_log(s) fprintf(stderr,"\033[1;31m%s%s\033[0m",log_anav_head, s); fflush(stderr)
#define anav_unmarked_log(s) fprintf(stderr,"\033[1;31m%s\033[0m", s); fflush(stderr)

#define anav_write(s) char output[BUFSIZE] = {0}; snprintf(output,BUFSIZE-1,"\033[1;31m%s%s\033[0m", log_anav_head, s); write(STDERR_FILENO, output, strlen(output));

static const char *log_anav_head = "[ANAV-LOG] ";
static const char *task_state[] = { "Ready", "Running", "Suspended", "Finished", "Killed", NULL };

/* Outputs an Introductory message at the start of the program */
void log_anav_intro() { 
  anav_log("Welcome to the ANAV Task Manager!\n");
  anav_log("\n");
}

/* Outputs the Help: All the Built-in Commands */
void log_anav_help() { 
  anav_log("Built-In Instructions:\n");
  anav_log("    COMMAND [ARGS...],\n");
  anav_log("    help, quit, list, purge TASK,\n");
  anav_log("    exec TASK [<INFILE] [>OUTFILE],\n");
  anav_log("    bg TASK [<INFILE] [>OUTFILE],\n");
  anav_log("    pipe TASK1 TASK2,\n");
  anav_log("    kill TASK, suspend TASK, resume TASK\n");
  anav_log("\n");
  anav_log("Brackets denote optional arguments\n");
}

/* Outputs the message after running quit */
void log_anav_quit(){
  anav_log("Thanks for using the ANAV Task Manager! Good-bye!\n");
}

/* Outputs the prompt */
void log_anav_prompt() {
  printf("ANAV$ ");
  fflush(stdout);
}

/* Outputs a notification of a task deletion */
void log_anav_purge(int task_num) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Purging Task #%d\n", task_num);
  anav_log(buffer);
}

/* Outputs a notification of an error due to action in an incompatible state. */
void log_anav_status_error(int task_num, int status) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Error acting on Task #%d due to process in %s state\n", task_num, task_state[status]);
  anav_log(buffer);
}

/* Outputs a notification of an file error */
void log_anav_file_error(int task_num, const char *file) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Error opening file %s for Task #%d\n", file, task_num);
  anav_log(buffer);
}

/* Notifies of an input or output redirection */
void log_anav_redir(int task_num, int redir_type, const char *file) {
  char buffer[BUFSIZE] = {0};
  static const char* types[] = {"input", "output"};
  static const char* polarity[] = {"from", "to"};
  if (redir_type < 0 || redir_type >= 2) {
	  anav_write("Invalid input to log_anav_redir\n");
	  return;
  }
  sprintf(buffer, "Redirecting %s %s %s for Task #%d\n", types[redir_type], polarity[redir_type], file, task_num);
  anav_log(buffer);
}

/* Outputs a notification of the creation of a pipe */
void log_anav_pipe(int task_id1, int task_id2) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Opening a pipe from Task #%d to Task #%d\n", task_id1, task_id2);
  anav_log(buffer);
}

/* Outputs a notification of an error piping a program's output to itself */
void log_anav_pipe_error(int task_num) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Error attempting to pipe Task #%d's output to itself\n", task_num);
  anav_log(buffer);
}

/* Output when the command is not found
 * eg. User typed in lss instead of ls and exec returns an error
 */ 
void log_anav_exec_error(const char *line) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Error: %s: Command Cannot Load\n", line);
  anav_log(buffer);
}

/* Output when activating a new task */
void log_anav_task_init(int task_num, const char *cmd) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Adding Task #%d: %s (Ready)\n", task_num, cmd);
  anav_write(buffer);
} 

/* Output when the given task number is not found */
void log_anav_task_num_error(int task_num) {
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "Error: Task #%d Not Found in Task List\n", task_num);
  anav_write(buffer);
}

/* Output when ctrl-c is received */
void log_anav_ctrl_c() {
  anav_write("Keyboard Combination control-c Received\n");
}

/* Output when ctrl-z is received */
void log_anav_ctrl_z() {
  anav_write("Keyboard Combination control-z Received\n");
}

/* Output when a signal is sent to a task's process */
void log_anav_sig_sent(int sig_type, int task_num, int pid) {
  char buffer[BUFSIZE] = {0};
  static const char* sigs[] = {"Suspend", "Resume", "Kill"};
  if (sig_type < 0 || sig_type >= 3) {
	  anav_write("Invalid input to log_anav_sig_sent\n");
	  return;
  }
  sprintf(buffer,"%s message sent to Task #%d (PID %d)\n", sigs[sig_type], task_num, pid);
  anav_log(buffer);
}

/* Output when a task changes state.
 * (Signal Handler Safe Outputting)
 */
void log_anav_status_change(int task_num, int pid, int type, const char *cmd, int transition) {
  char buffer[BUFSIZE] = {0};
  static const char* msgs[] = {"Terminated Normally", "Terminated by Signal", "Continued", "Stopped", "Started"};
  static const char* types[] = {"Foreground", "Background"};
  if (transition < 0 || transition >= 5 || type < 0 || type >= 2) {
	  anav_write("Invalid input to log_anav_status_change\n");
	  return;
  }
  sprintf(buffer,"%s Process %d (Task %d): %s (%s)\n",types[type], pid, task_num, cmd, msgs[transition]);
  anav_write(buffer);
}

/* Output to list the task counts */
void log_anav_num_tasks(int num_tasks){
  char buffer[BUFSIZE] = {0};
  sprintf(buffer, "%d Task(s)\n", num_tasks);
  anav_log(buffer);
}

/* Output info about a single task */
void log_anav_task_info(int task_num, int status, int exit_code, int pid, const char *cmd){
  char buffer[BUFSIZE] = {0};
  if (status < 0 || status >= 5) {
	  anav_write("Invalid input to log_anav_task_info\n");
	  return;
  }
  if (!cmd) 
  { sprintf(buffer, "Task #%d: (%s)\n", task_num, task_state[status]); }
  else if (!pid) 
  { sprintf(buffer, "Task #%d: %s (%s)\n", task_num, cmd, task_state[status]); }
  else if (status != LOG_STATE_FINISHED && status != LOG_STATE_KILLED) 
  { sprintf(buffer, "Task #%d: %s (PID %d; %s)\n", task_num, cmd, pid, task_state[status]); }
  else
  { sprintf(buffer, "Task #%d: %s (PID %d; %s; exit code %d)\n", task_num, cmd, pid, task_state[status], exit_code); }

  anav_log(buffer);
}
