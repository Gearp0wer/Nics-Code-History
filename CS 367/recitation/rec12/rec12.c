#include <stdio.h>   /* printf  */
#include <string.h>  /* strncmp, strdup */
#include <stdlib.h>  /* atoi, strtol    */
#include <malloc.h>  /* malloc, free    */

extern long     call_dot4 ();
extern long     dot4 (long, long, long, long, long, long, long, long);
extern long    	call_scale ();
extern void    	scale (long*, long*, long);
extern long     call_sum (long, long);
extern long     pow2 (long);
extern long     rec_fib (long);

static int check_func_params(const char *prog, const char *funcname, int argc, int req);

/*
 A helper function which makes sure we have enough input args.
 prog is the program's name
 funcname is the name of the function;
 argc is the program's argc;
 req is the required number of function inputs;
 If the number of args is ok, then returns true, otherwise prints an error message and quits.
*/
static int check_func_params(const char *prog, const char *funcname, int argc, int req) {
    if (argc == req + 2) return 1;
    fprintf(stderr, "error - wrong number of arguments.\n\n");
    fprintf(stderr, "\tusage: %s %s", prog, funcname);
    for (int i = 1; i <= req; i++) { fprintf(stderr, " arg%d", i); }
    fprintf(stderr, "\n\n");
    exit(1);
}

/*
receives command line arguments for:
 #1 function to be tested
 #2 first argument
 (#3+: more arguments, or array values for the last argument)
*/
int main(int argc, char ** argv){
  /* check for minimum number of arguments */
  if (argc<2){
    printf("error - not enough arguments.\n\n\tusage: %s funcname [args ...]\n\n", argv[0]);
    return 1;
  }

  /* convert the inputs to numbers, wherever possible. */
  long *inputs = calloc(argc, sizeof(long));  // create an array to store the number
  long *arg = inputs + 1;
  if (!inputs) {
    fprintf(stderr, "error - memory allocation failed.\n\n");
    return 1;
  }
  memset(inputs, 0, argc * sizeof(long));    // default to all zeros
  for (int i = 2; i < argc; i++) {           // loop and load the args
    inputs[i] = strtol(argv[i], NULL, 0);    // conver string to long (accepts both hex and decimal, zero on err)
  }
  
  /* dispatch to the correct function */
  char *progName = argv[0];
  char *funcName = argv[1];
  
  if ( ! strncmp("call_dot4", funcName, 10)){
    check_func_params(progName, funcName, argc, 0);
    printf("%ld\n", call_dot4());
  }
  
  else if ( ! strncmp("dot4", funcName, 5)){
    check_func_params(progName, funcName, argc, 8);
    printf("%ld\n", dot4(arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8]));
  }
  
  else if ( ! strncmp("call_scale", funcName, 10)){
    check_func_params(progName, funcName, argc, 0);
    printf("%ld\n", call_scale());
  }
 
  else if ( ! strncmp("scale", funcName, 5)){
    check_func_params(progName, funcName, argc, 3);
    long arg1 = arg[1], arg2 = arg[2], s = arg[3];
    scale(&arg1, &arg2, s);
    printf("%ld, %ld\n", arg1, arg2);
  }
 
  else if ( ! strncmp("call_sum", funcName, 10)){
    check_func_params(progName, funcName, argc, 2);
    long x = arg[1], y = arg[2];
    printf("%ld\n", call_sum(x, y));
  }
  
  else if ( ! strncmp("pow2", funcName, 5)){
    check_func_params(progName, funcName, argc, 1);
    long x = arg[1];
    printf("%ld\n", pow2(x)); 
  }
 
  else if ( ! strncmp("rec_fib", funcName, 10)){
    check_func_params(progName, funcName, argc, 1);
    long x = arg[1];
    printf("%ld\n", rec_fib(x)); 
  }
 
  /* give a helpful message when the function is misspelled. */
  else {
    printf("error - unrecognized command '%s'.\n",argv[1]);
    return 2;
  }
}
