#include <stdio.h>   /* printf  */
#include <string.h>  /* strncmp, strdup */
#include <stdlib.h>  /* atoi, strtol    */
#include <malloc.h>  /* malloc, free */

extern long       checkeq (long, long);
extern long         power (long, long);
extern long      countPos (long*, long);
extern long     middleSum (long, long);
extern long collatzLength (long);

static int check_func_params(const char* prog, const char* funcname, int argc, int req);

/*
 A helper function which makes sure we have enough input args.
 prog is the program's name
 funcname is the name of the function;
 argc is the program's argc;
 req is the required number of function inputs;
 If the number of args is ok, then returns true, otherwise prints an error message and quits.
*/
static int check_func_params(const char* prog, const char* funcname, int argc, int req) {
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
  if (argc<3){
    fprintf(stderr, "error - not enough arguments.\n\n\tusage: %s funcname arg1 [arg2 arg3 ...]\n\n", argv[0]);
    return 1;
  }

  /* convert the inputs to numbers, wherever possible. */
  long *inputs = calloc(argc, sizeof(long));  // create an array to store the number
  long *arg = inputs + 1;                     // the args themselves start at offset 2, so args[1] would be arg1.
  if (!inputs) {
    fprintf(stderr, "error - memory allocation failed.\n\n");
    return 1;
  }
  memset(inputs, 0, argc * sizeof(long));     // default to all zeros
  for (int i = 2; i < argc; i++) {            // loop and load the args
    inputs[i] = strtol(argv[i], NULL, 0);     // convert string to long (accepts both hex and decimal, zero on err)
  }

  /* dispatch to the correct function */
  char* progName = argv[0];
  char* funcName = argv[1];
  
  if ( ! strncmp("checkeq", funcName, 10)) { 
    check_func_params(progName, funcName, argc, 2);
    long a = arg[1], b = arg[2];
    printf("%ld\n", checkeq(a, b));
  } 
  
  else if ( ! strncmp("power", funcName, 10)){
    check_func_params(progName, funcName, argc, 2);
    long x = arg[1], n = arg[2];
    printf("%ld\n", power(x, n));
  }
  
  else if ( ! strncmp("countPos", funcName, 15)) {
    //check_func_params(progName, funcName, argc, 1);
    long n = argc - 2;
    long *arr = calloc(n, sizeof(long));
    if (!arr) {
        fprintf(stderr, "error - memory allocation failed.\n\n");
        return 1;
    }
    for (int i = 0; i < n;  i++) {
        arr[i] = arg[i+1];
    }
    printf("%ld\n", countPos(arr, n));
    free(arr);
  }
  
  else if ( ! strncmp("middleSum",funcName,10)){
    check_func_params(progName, funcName, argc, 2);
    long x = arg[1];
    long y = arg[2];
    printf("%ld\n", middleSum(x, y));
  }

  else if ( ! strncmp("collatzLength",funcName,15)){
    check_func_params(progName, funcName, argc, 1);
    long x = arg[1];
    printf("%ld\n", collatzLength(x));
  }
  
  
  /* give a helpful message when the function is misspelled. */
  else {
    fprintf(stderr, "error - unrecognized command '%s'.\n", funcName);
    free(inputs);
    return 2;
  }

  free(inputs);
  return 0;
}
