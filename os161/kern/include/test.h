#ifndef _TEST_H_
#define _TEST_H_

/*
 * Declarations for test code and other miscellaneous functions.
 */


/* Stoplight problems. Only available for ASST1. */
#ifdef OPT_SYNCHPROBS
int stoplight_simple(int, char**);
int stoplight_random(int, char**);
int stoplight_prio(int, char**);
int stoplight_custom(int, char**);
#endif

/*
 * Test code.
 */

/* lib tests */
int arraytest(int, char **);
int bitmaptest(int, char **);
int queuetest(int, char **);

/* thread tests */
int threadtest(int, char **);
int threadtest2(int, char **);
int threadtest3(int, char **);
int semtest(int, char **);
int locktest(int, char **);
int cvtest(int, char **);

/* filesystem tests */
int fstest(int, char **);
int readstress(int, char **);
int writestress(int, char **);
int writestress2(int, char **);
int createstress(int, char **);
int printfile(int, char **);

/* other tests */
int malloctest(int, char **);
int mallocstress(int, char **);
int nettest(int, char **);

/* Kernel menu system */
void menu(char *argstr);
void hello(void);
/* Routine for running userlevel test code. */
int runprogram(char *progname);

#endif /* _TEST_H_ */
