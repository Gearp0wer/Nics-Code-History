/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name: Nicholas Locklear
 * GNumber: G01090642
 */

#include <sys/wait.h>
#include "buffermngr.h"
#include "parse.h"
#include "util.h"

/* Constants */
#define DEBUG 1

/*
static const char *textproc_path[] = { "./", "/usr/bin/", NULL };
static const char *instructions[] = { "quit", "help", "list", "new", "open", "write", "close", "print", "active", "pause", "resume", "cancel", "exec", NULL};
*/

/* The entry of your text processor program */

//helper functions up here

/**
 * TODO: 
 *  argv: an array of NULL terminated char pointers with the similar format requirement
as the one used in execv().
o argv[0] should be the name of the program to be loaded and executed;
o the remainder of argv[] should be the list of arguments used to run the
program
o argv[] must have NULL following its last argument member


go in and alter any arg calls to make sure they are correct!!!!
 * 
 */


typedef struct TaskStruct {
    int PID;
//int activityStatus; //0 is active, 1 is background //keep this just in case!!!!
    int State;
    int ExitCode;
    Instruction *Task;
	
    struct TaskStruct *next; 
    struct TaskStruct *prev;
}node;

node *Head = NULL; //lowest tasknum
node *Tail= NULL; //highest tasknum
node *activeNode = NULL;
int HighestTask = 0;


bool isEmpty() {
   return (Head == NULL);
}

int bufLength() {
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
  
int nodeInit(node *holderStruct){
    if (!holderStruct ){ return 0;}
    holderStruct->State = 0;
    holderStruct->ExitCode = 0;
    holderStruct->PID = 0;
    holderStruct->Task = NULL;
    holderStruct->next = NULL;
    holderStruct->prev = NULL;
    return 1;
}
node* findBufID(int bufID){
    node* current = Head;
    //printf("length check 1\n");
    if (isEmpty() == false){
        while(current !=NULL){
            //printf("length check %d\n", current->Task->id);
            if(current->Task->id == bufID){return current;}
            current = current->next;
        }
        return Head;

    }
    return current;
}
// phase the below out
/**
Instruction* activeNode{//todo: add in error handling for this-returns head!
    node* current = Head;
    //printf("length check 1\n");
    if (isEmpty() == false){
        while(current != NULL){
            if(current->State == LOG_ACTIVE){
printf("In the weeds now: NODE ID: %d, NODE STATE = %d????\n", current->Task->id, current->State);

                return current->Task;
            }
current = current->next;
        }
    }
    else{
printf("Active is trying to pass null???? uh oh\n");

        return current->Task; 
    }
    return current->Task;
}
*/
int NodeFree(node *input){ //rewrite this, check for errors?
    if(!input){return 0;}
    free_instruction(input->Task);
    input->Task = NULL;
    input->next = NULL; 
    input->prev = NULL;
    return 1;
}



//-------------------------------------------------------------------------------------------------------------------------

void reaper(int sig) {
    printf("reap: %d\n",sig);
    if(sig ==2){
        log_ctrl_c();
        //exit(0);
    }
    if(sig == 20){
        log_ctrl_z();
        //exit(0);
    }
    if(sig == 1){
        printf("reap\n");
    }
    return;
}
//-------------------------------------------------------------------------------------------------------------------------

int newBuffer(Instruction* Buffer){//when called, create new open buffer 1 if successful
    //init all
        node *Holder = (node*)malloc(sizeof(node));
    int status = nodeInit(Holder);
    if(status == 0){}//catastrophic error, abort}
    Holder->Task = Buffer;
    Holder->Task->id = HighestTask +1;
    HighestTask +=1;
    log_open(HighestTask);
    log_activate(HighestTask);
    if(isEmpty()){
        Head = Holder;
        Tail = Holder;    
        //log_activate(Holder->Task->id);//lowest node
        Holder->State = LOG_STATE_READY;
        activeNode = Holder;
    }
    else{ //inserts at Back of list
        Holder->State = LOG_STATE_READY;
        Tail->next =Holder; 
        Holder->prev = Tail;
        Tail = Holder;
activeNode = Holder;
    }
    return 1;
}


int listBuffer(){ //check for null, 0, unexpected values
    int bufferLength = bufLength();
    log_buf_count(bufferLength);
        if(bufferLength == 0){
            log_show_active(0);
            return 1;
            }
    node* dummyHead = Head;
    node* activeLocalNode = activeNode;
    while(dummyHead != NULL){
                log_buf_details(dummyHead->Task->id,dummyHead->State,dummyHead->Task->id,dummyHead->Task->instruct);
        dummyHead = dummyHead->next;
    }
    log_show_active(activeLocalNode->Task->id);
    return 1;
}


int activateBuffer(int id){ //clarify the conditions for the states
if(id == 0){
       log_activate(activeNode->Task->id);
       return 1;
    }
    node* dummyHead = Head;
    if(dummyHead == NULL){ //cant risk asking findActive() to return a null
        log_buf_id_error(id);
        //printf("head is null???? weird\n");
        return 0;
    }
//printf("id: %d\n", id);
    while(dummyHead != NULL){
        if(id == dummyHead->Task->id){
           activeNode = dummyHead;
        log_activate(activeNode->Task->id);
            //printf("Current Active id: %d\n", activeNode->Task->id);
            return 1;
        }
        dummyHead = dummyHead->next;
    }
    log_buf_id_error(id); //id missing!!
        return 0;
    }


int closeBuffer(int bufID){
    node* dummyHead = Head;
        if(dummyHead == NULL){
        log_buf_id_error(0);
        return 0;
    }
    //printf(" locating: %d\n", bufID);
    if(bufLength() == 0){
        log_buf_id_error(bufID);
        return 0;
    }
    if(bufLength() == 1){//only one 
        NodeFree(dummyHead);
        activeNode = NULL;
        Head = NULL;
        Tail = NULL;
        log_close(bufID);
        log_show_active(0);
        return 1;
    }
    while(dummyHead != NULL){
//    printf("Currently At ID: %d\n", dummyHead->Task->id);
        if(bufID == dummyHead->Task->id){
            if(dummyHead->State != LOG_STATE_READY){
                log_close_error(bufID);
                return 0;
            }
            else{
                if(activeNode == dummyHead){activeNode = Tail;}
                if(dummyHead->next != NULL && dummyHead->prev != NULL){
                    dummyHead->prev->next = dummyHead->next;
                    dummyHead->next->prev = dummyHead->prev;
                }
                else if(dummyHead->next == NULL){
                    Tail = dummyHead->prev;
                    activeNode = Tail;
                    dummyHead->prev->next = NULL;}
                else if(dummyHead->prev ==NULL){
                    Head = dummyHead->next;
                    dummyHead->next->prev = NULL;}
                log_close(bufID);
                NodeFree(dummyHead);
                return 0;

        }
    }
    dummyHead = dummyHead->next;
    }
        log_buf_id_error(bufID);
        return 0;
    }


void openBuffer(Instruction* instructionStruct){

    //create new buffer, set to active. set contents as empty if file fails to open
    newBuffer(instructionStruct);
    int fd = open(instructionStruct->file, O_RDWR);
        if (fd == -1){
        //printf("filerror\n");
        log_file_error(LOG_FILE_OPEN_READ, instructionStruct->file);
        }
    else{
        instructionStruct->instruct = fd_to_text(fd);
        log_read(instructionStruct->id, instructionStruct->file);
    //printf("file Read?\n");

    }
    close(fd);
return;
}


void printBuffer(int bufID){
    if(bufID == 0){//active
        log_print(activeNode->Task->id, activeNode->Task->instruct);
    }
    else{
         node* idNode = findBufID(bufID);
        if(idNode->Task->id != bufID){
            log_buf_id_error(bufID);
            }
        else{
            log_print( idNode->Task->id, idNode->Task->instruct);
        }
    }
    return;
}


void writeActive(Instruction* instStruct){ //currently writes "write" to file
    char* filename = instStruct->file;    
    Instruction *activeLocalNode = activeNode->Task;
 //   int fd = open(filename, O_TRUNC);
//    int textToDD = text_to_fd(instStruct->instruct, fd);
    //printf("filename %s\n", instStruct->file);
    int fd = open(instStruct->file, O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);
    if (fd == -1) {
        log_file_error(LOG_FILE_OPEN_WRITE, filename);
        close(fd);
        fd = open(filename,  O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    //printf("Is it me, Jesus?\n");
    }
    //printf("fileopen is clean?\n");
    text_to_fd(activeLocalNode->instruct, fd);  //todo: this output might be incorrect, find sample
    log_write(activeLocalNode->id, filename);
    close(fd);
    free(filename);
    return ;
}


void writebufID(Instruction* instruction_struct){
    //printf("ID: %d\n", instruction_struct->id);
    char* filename = instruction_struct->file;
    if(instruction_struct->id == 0){
        writeActive(instruction_struct);
        return;
    }
    else{   
    int fd = 0;
    node* bufInstruction = findBufID(instruction_struct->id);
    if(bufInstruction->Task->id != instruction_struct->id){ //id not available
        //printf("ID Mismatch? Given: %d, found: %d\n",instruction_struct->id, bufInstruction->Task->id);
        log_buf_id_error(bufInstruction->Task->id);
        fd = open(filename, O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);
    }
    else{ //available, overwrite
        fd = open(filename, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    }
    if(fd == -1){log_file_error(LOG_FILE_OPEN_WRITE, filename);}
    text_to_fd(bufInstruction->Task->instruct, fd);  //todo: this output might be incorrect, find sample

    log_write(bufInstruction->Task->id, filename);
    close(fd);
    }
    return ;
}


void execID(Instruction* instruction_struct, char** argv, char* cmd){
    struct sigaction sa = {0};
    sa.sa_handler = reaper;
    sigaction(SIGCHLD, &sa, NULL);
    if(instruction_struct == NULL){
        //printf("null...!\n");
        return;
    }
    //printf("searching for id...!\n");
    //if active
    node* instructionNode;
    if(instruction_struct->id == 0){
        //printf("id = active...!\n");
        instructionNode = activeNode;
    }
    //if not
    else{
        //printf("id = %d...!\n", instruction_struct->id);       
        instructionNode =  findBufID(instruction_struct->id);

        if(instruction_struct->id != instructionNode->Task->id){
            log_buf_id_error(instruction_struct->id);
            //printf("bad id?!\n");
            return;
        }
    }

    if(instructionNode->State != LOG_STATE_READY ){
        log_cmd_state_conflict(instruction_struct->id, instructionNode->State);
        //printf("\nINACTIVE!!!\n");
        return;
    }

    //int pipefd[2] = {0};
    //printf("forked!\n");
    pid_t pid = fork();
    instructionNode->PID = getpid();
    if(pid == 0){ //child
       // printf("child!\n");
        setpgid(0,0);
        //exit(0);
        char path[50]  = " ";
        if(activeNode->Task->file != NULL){
            char path[50]  = "./ ";
            strcat(path,instructionNode->Task->file); //in both these cases, redirect execv output back to the buffer on succes
        }


        //close(pipefd[0]); // Close unused read end
        //dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        //dup2(pipefd[1], STDERR_FILENO); // Optional: Redirect stderr to pipe as well
        //close(pipefd[1]); 
        //printf("path1 %s\n", path);
        
        if(execv(path,argv) == -1){
            char path2[50]  = " ";
            //printf("child2!\n");
            if(activeNode->Task->file != NULL){
                char path2[50]  = "/usr/bin/ ";
                strcat(path2,instructionNode->Task->file);
            }
            
            //printf("%s\n",path);            
            //printf("%s\n",path2);
            if(execv(path2,argv) ==-1){
                log_command_error(cmd);
                //printf("child out 1!\n");
                activeNode->ExitCode = 1;
                exit(1);
            }
            else{
                activeNode->State = LOG_STATE_WORKING;
                //printf("child out 2!\n");
                activeNode->ExitCode = 0;
                exit(0);
            }
        }
        else{
            //signal(SIGINT,reaper);
            //printf("[execv/: success]!\n");
            //printf("child out 3!\n");
            activeNode->ExitCode = 1;
            exit(1);
        }  
        //printf("how did i get here?\n");
        printf("child out 4!\n");
        activeNode->ExitCode = 0;
        activeNode->State = LOG_STATE_WORKING;
        exit(0);
    }
    else{ //parent
        log_start(instructionNode->Task->id, pid, LOG_ACTIVE, cmd);
        //close(pipefd[1]);
        //instructionNode->Task->instruct = fd_to_text(pipefd[0]);
        //close(pipefd[0]);
        int sighandle = 0;
        waitpid(pid, &sighandle, 0);
        printf("sighandle??? %d\n", sighandle);
        log_cmd_state(pid,instructionNode->State, cmd, 0);
        activeNode->State = LOG_STATE_READY;
    }
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cancelID(int bufID){
    node* instructionNode = activeNode;
    if(bufID == 0){
        //printf("id = active...!\n");
        instructionNode = activeNode;
    }
    else{
        node* instructionNode = findBufID(bufID);
        if(instructionNode->Task->id != bufID){
            log_buf_id_error(bufID);
            return;
        }
    }
    int pid = 0;
    int state = 0;
    pid = instructionNode->PID;
    state = instructionNode->State;
    if (state == LOG_STATE_WORKING || state == LOG_STATE_PAUSED) {

        int result = kill(pid, SIGINT);
        if (result == 0) {
            log_cmd_signal(LOG_CMD_CANCEL, bufID);
        } 
        else {
            log_buf_id_error(bufID);
            // Log error if required
        }
    } 
    else if (state == LOG_STATE_READY) {
        log_cmd_state_conflict(bufID, state);
    }
}


void pauseID(int bufID){
    node* instructionNode = activeNode;
    if(bufID == 0){
        //printf("id = active...!\n");
        instructionNode = activeNode;
    }
    else{
        node* instructionNode = findBufID(bufID);
        if(instructionNode->Task->id != bufID){
            log_buf_id_error(bufID);
            return;
        }
    }
    int pid = 0;
    int state = 0;
    pid = instructionNode->PID;
    state = instructionNode->State;
    if (state == LOG_STATE_WORKING || state == LOG_STATE_PAUSED) {

        int result = kill(pid, SIGTSTP);
        if (result == 0) {
            log_cmd_signal(LOG_CMD_PAUSE, bufID);
        } 
        else {
            log_buf_id_error(bufID);
            // Log error if required
        }
    } 
    else if (state == LOG_STATE_READY) {
        log_cmd_state_conflict(bufID, state);
    }
}


void resumeID(int bufID){
    node* instructionNode= activeNode;
    if(bufID == 0){
        //printf("id = active...!\n");
        instructionNode = activeNode;
    }
    else{
        node* instructionNode = findBufID(bufID);
        if(instructionNode->Task->id != bufID){
            log_buf_id_error(bufID);
            return;
        }
    }
    int pid = 0;
    int state = 0;
    pid = instructionNode->PID;
    state = instructionNode->State;
    if (state == LOG_STATE_WORKING || state == LOG_STATE_PAUSED) {
        int result = kill(pid, SIGCONT);
        if (result == 0) {
            log_cmd_signal(LOG_CMD_RESUME, bufID);
        } 
        else {
            log_buf_id_error(bufID);
            // Log error if required
        }
    } 
    else if (state == LOG_STATE_READY) {
        log_cmd_state_conflict(bufID, state);
    }   
}


//-------------------------------------------------------------------------------------------------------------------------


int main() {
    char cmdline[MAXLINE];        /* Command line */
    char *cmd = NULL;

    /* Intial Prompt and Welcome */
    log_help();

    /* Shell looping here to accept user command and execute */
    while (1) {
        char *argv[MAXARGS];        /* Argument list */
        Instruction inst;           /* Instruction structure: check parse.h */

        /* Print prompt */
        log_prompt();

        /* Read a line */
        // note: fgets will keep the ending '\n'
	errno = 0;
        if (fgets(cmdline, MAXLINE, stdin) == NULL) {
            if (errno == EINTR) {
                continue;
            }
            exit(-1);
        }

        if (feof(stdin)) {  /* ctrl-d will exit text processor */
          exit(0);
        }

        /* Parse command line */
        if (strlen(cmdline)==1)   /* empty cmd line will be ignored */
          continue;     
        cmdline[strlen(cmdline) - 1] = '\0';        /* remove trailing '\n' */

        cmd = malloc(strlen(cmdline) + 1);
        snprintf(cmd, strlen(cmdline) + 1, "%s", cmdline);

        /* Bail if command is only whitespace */
        if(!is_whitespace(cmd)) {
            initialize_command(&inst, argv);    /* initialize arg lists and instruction */
            parse(cmd, &inst, argv);            /* call provided parse() */

            if (DEBUG) {  /* display parse result, redefine DEBUG to turn it off */
                debug_print_parse(cmd, &inst, argv, "main (after parse)");
	        }

            /* After parsing: your code to continue from here */          //figure out how parsing i
            /*================================================*/
            Instruction* InstructionStruct = (Instruction*) malloc(sizeof(InstructionStruct));
            char *argvCopy[MAXARGS+1] = {0};
            parse(cmd,InstructionStruct,argvCopy);
            //int returncode;

            if(strncmp(cmd, "help", 4) == 0){
                log_help();
            }
            else if(strncmp(cmd, "list", 4) == 0){
                listBuffer();
            }
            else if(strncmp(cmd, "quit", 4) == 0){
                log_quit();
                exit(0);
            }
            else if(strncmp(cmd, "active", 6) == 0){
                activateBuffer(InstructionStruct->id);
            }
            else if(strncmp(cmd, "close", 5) == 0){
                closeBuffer(InstructionStruct->id);
            }
            else if(strncmp(cmd, "open", 4) == 0){ //argv should hold the info needed for read/write/print
                openBuffer(InstructionStruct);
            }
            else if(strncmp(cmd, "write", 5) == 0){
                writebufID(InstructionStruct);
            }
            else if(strncmp(cmd, "print", 5) == 0){
                printBuffer(InstructionStruct->id); 
            }
            else if(strncmp(cmd, "exec", 4) ==0){
                //printf("called!\n");
                execID(InstructionStruct,argvCopy, cmd); //just pass in the node ??
            }
            else if(strncmp(cmd, "new", 4) ==0){
                
                if(argvCopy[0] != NULL){ //this works
                    newBuffer(InstructionStruct);
                    //node* instructionNode = findBufID(InstructionStruct->id);
                    execID(InstructionStruct,argvCopy, cmd);
                    printf("newcmd\n");
                }
                else{
                    newBuffer(InstructionStruct);
                    //printf("newblank\n");

                }
            }
            else if(strncmp(cmd, "cancel", 6) == 0){
                cancelID(InstructionStruct->id);
            }
////////////////////

            else if(strncmp(cmd, "pause", 5) == 0){
                pauseID(InstructionStruct->id);
            }

            else if(strncmp(cmd, "resume", 6) == 0){
                resumeID(InstructionStruct->id);
            }
            else{

                newBuffer(InstructionStruct); //copy in argv and cmd const w utils.c, figure out when to free?
                //printf("newblank\n");

            }


	    
        }

	free(cmd);
	cmd = NULL;
        free_command(&inst, argv);
    }
    return 0;
}



