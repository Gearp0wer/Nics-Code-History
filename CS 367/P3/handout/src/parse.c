/* DO NOT modify this file.
 * This is the provided parsing facility. 
 * You can call parse() to divide the user command line into useful pieces. */

#include <stdio.h>
#include <stdarg.h>

#include "parse.h"
#include "anav.h"
#include "util.h"

/* Helper Functions */
static void parse_n(const char *cmd_line, Instruction *inst, char *argv[], size_t n);
static int initialize_argv_n(char *argv[], size_t n);
static int contains(const char *needle, char *haystack[]);
static int parse_num_token(char *inst_list[], const char *p_tok, const char *instruct, int *id1);
static int parse_file_token(char *inst_list[], char **p_toks, const char *instruct, char **infile, char **outfile);
char **get_redirect_file(char **p_toks, char **file);
static int is_redirect_in(const char *p_tok);
static int is_redirect_out(const char *p_tok);
static void DPRINTF(const char* fmt, ...); 

/* Reference Data */

// full recognized instruction list
static char *instructs_list_full[] = {"quit", "help", "list", "purge", "exec", "bg", "kill", "suspend", "resume", "pipe", NULL};

// instructions which may use an Task Number argument
static char *instructs_with_id1[] = {"purge", "exec", "bg", "kill", "suspend", "resume", "pipe", NULL};

// instructions which may use a 2nd Task Number argument
static char *instructs_with_id2[] = {"pipe", NULL};

// instructions which may use filename arguments
static char *instructs_with_file[] = {"exec", "bg", NULL};

/*********
 * Command Parsing Functions
 *********/

char *get_input() {
  char buffer[MAXLINE] = {0};

  /* Step 0: Read in the line from the user */
  errno = 0;
  if(fgets(buffer, MAXLINE, stdin) == NULL) {
    if(errno == EINTR) {
      return NULL;
    }
    exit(1);
  }

  /* Step 1: Check for Termination Condition (input stream closed) */
  if(feof(stdin)) {
    exit(0);
  }

  /* Step 2: Check for empty entries */
  if(strlen(buffer) == 1) {
    return NULL;
  }

  /* Step 3: Strip the newline */
  strtok(buffer, "\n");

  /* Step 4: Check for only whitespace */
  if(is_whitespace(buffer)) {
    return NULL;
  }
  
  /* Step 5: Copy the buffer to the command and return it */
  char *cmdline = calloc(strlen(buffer) + 1, sizeof(char));
  if(cmdline == NULL) {
    exit(2);
  }
  strncpy(cmdline, buffer, strlen(buffer) + 1);

  return cmdline;
}

void parse(const char *cmd_line, Instruction *inst, char *argv[]) {
    initialize_argv_n(argv, MAXARGS+1);
    parse_n(cmd_line, inst, argv, MAXARGS);
}

static void parse_n(const char *cmd_line, Instruction *inst, char *argv[], size_t n) {
  /* Step 0: ensure a valid input, and quit gracefully if there isn't one. */
    if (!cmd_line || !inst || !argv) return;

  /* Step 0b: ensure initialized data */
    initialize_instruction(inst);

  /* Step 1: Only work on a copy of the original command */ 
    char *p_tok = NULL;
    char buffer[MAXLINE] = {0};
    strncpy(buffer, cmd_line, MAXLINE);

  /* Step 2: Tokenize the inputs (space delim) and parse */
    p_tok = strtok(buffer, " ");
    if (p_tok == NULL) { return; }

    int index = 0;

    // copy the tokens into argv
    while(p_tok != NULL) {
        argv[index] = string_copy(p_tok);
	index++;
        p_tok = strtok(NULL, " ");
	if (index >= n) p_tok = NULL;
    }

    /* Step 2a: Parse the instruction */
    inst->instruct = string_copy(argv[0]);

    /* Step 2b: Parse the Task Number */
    parse_num_token(instructs_with_id1, argv[1], inst->instruct, &inst->id1);

    /* Step 2c: Parse the 2nd Task Number */
    parse_num_token(instructs_with_id2, argv[2], inst->instruct, &inst->id2);

    /* Step 2d: Parse the file names */
    parse_file_token(instructs_with_file, argv+2, inst->instruct, &inst->infile, &inst->outfile);

    /* Step 3: if the instruction is a built-in, clear argv */
    if (contains(inst->instruct, instructs_list_full)) {
        free_argv_str(argv);
    }
}



/* Parse the Task Number from the current token.  If the input is a valid number
 * token, and it corresponds to an appropriate instruction, then return true, 
 * else return false.  The id1 argument is populated with the number taken from p_tok.
 */
static int parse_num_token(char *inst_list[], const char *p_tok, const char *instruct, int *id1) {
    // sanity check whether we have a valid input
    if (!inst_list || !p_tok || !instruct || !id1) { return 0; }

    // only instructions in the inst_list are under consideration
    if (!contains(instruct, inst_list)) { return 0; }

    // attempt to read a number from the token
    char *end = NULL;
    *id1 = (int) strtol(p_tok, &end, 10);

    // check if we successfully read a valid ID number
    if (!end || (*end) || end == p_tok) {
        *id1 = 0;
	return 0;
    }

    return 1;
}

/* Parse a file name from the current token(s).  If the input is a valid redirect 
 * token, and it corresponds to an appropriate instruction, then return true, 
 * else return false.  The file arguments are populated with the file name(s) taken 
 * from p_toks.
 */
static int parse_file_token(char *inst_list[], char **p_toks, const char *instruct, char **infile, char **outfile) {
    // sanity check for valid input
    if (!inst_list || !p_toks || !instruct || !infile || !outfile) { return 0; }

    // only instructions in the inst_list are under consideration
    if (!contains(instruct, inst_list)) { return 0; }

    int found = 0;

    // search through all remaining tokens for redirect
    while (p_toks && *p_toks) {

        // check if we see '<'
        if (is_redirect_in(*p_toks)) {
            // found it! get the filename
            p_toks = get_redirect_file(p_toks, infile);
            found = 1;

        // check if we see '>'
        } else if (is_redirect_out(*p_toks)) {
            // found it! get the filename
            p_toks = get_redirect_file(p_toks, outfile);
            found = 1;

        // found nothing yet; move on
        } else { p_toks++; }
    }

    return found;
}

char **get_redirect_file(char **p_toks, char **file) {
    // sanity check for valid input
    if (!p_toks || !p_toks[0] || !file) return NULL;

    // let p_tok be the character after the redirect symbol int p_toks[0]
    const char *p_tok = p_toks[0] + 1;

    // if no string, check the next spot instead
    if (!*p_tok) {
        p_toks++;
        p_tok = p_toks[0];
    }
    
    // make a copy of the string we found
    *file = string_copy(p_tok);

    // return a pointer to the next argument
    return p_toks + 1;
}

// check whether the current token is or starts with an input redirection, "<"
static int is_redirect_in(const char *p_tok) {
    if (!p_tok) return 0;
    return (p_tok[0] == '<');
}

// check whether the current token is or starts with an output redirection, ">"
static int is_redirect_out(const char *p_tok) {
    if (!p_tok) return 0;
    return (p_tok[0] == '>');
}

/* Returns true of false depending on whether the haystack contains the needle. */
static int contains(const char *needle, char *haystack[]) {
    // sanity check for valid input
    if (!needle || !haystack) return 0;

    // search through the haystack string-by-string until we find a match
    for (int i = 0;  haystack[i];  i++) {
        if (strncmp(needle, haystack[i], strlen(haystack[i]) + 1) == 0) { return 1; }
    }
    return 0;
}

/*********
 * String Processing Helpers
 *********/

/* Returns 1 if string is all whitespace, else 0 */
int is_whitespace(const char *str) {
    if (!str) return 1;
    while (isspace(*str)) { str++; }  // skip past every whitespace character
    return *str == '\0';  // decide based on whether the first non-whitespace is the end-of-string
}

/*********
 * Initialization Functions
 *********/

int initialize_instruction(Instruction *inst) {
    if (!inst) return 0;

    inst->instruct = NULL;
    inst->id1 = 0;
    inst->id2 = 0;
    inst->infile = NULL;
    inst->outfile = NULL;

    return 1;
}

int initialize_argv(char *argv[]) {
    return initialize_argv_n(argv, MAXARGS+1);
}

static int initialize_argv_n(char *argv[], size_t n) {
    if (!argv) return 0;

    for(int i = 0; i < n; i++) {
        argv[i] = NULL;
    }
    return 1;
}

int initialize_command(Instruction *inst, char *argv[]) {
    if (! initialize_instruction(inst)) return 0;
    if (! initialize_argv(argv)) return 0;
    return 1;
}


void free_instruction(Instruction *inst) {

    if (inst) {
        free(inst->instruct);
	inst->instruct = NULL;
	free(inst->infile);
	inst->infile = NULL;
	free(inst->outfile);
	inst->outfile = NULL;
    }

}

void free_command(char *cmd, Instruction *inst, char *argv[]) {
  free(cmd);
  free_instruction(inst);
  free_argv_str(argv);
}

/*********
 * Debug Functions
 *********/
static void DPRINTF(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buf[256] = {0};
	snprintf(buf, 256, "\033[1;33m[DEBUG] %s\033[0m", fmt);
	vfprintf(stderr, buf, args);
	va_end(args);
}

void debug_print_parse(char *cmdline, Instruction *inst, char *argv[], char *loc) {
    int i = 0;
    fprintf(stderr, "\n");
    DPRINTF("-----------------------\n");
    if (loc) { DPRINTF("- %s\n", loc); }
    if (loc) { DPRINTF("-----------------------\n"); }

    if(cmdline) { DPRINTF("cmdline     = %s\n", cmdline); }
  
    if(inst) {
        DPRINTF("instruction = \"%s\"\n", inst->instruct);
        if (inst->id1) { DPRINTF(" 1st task # = %d\n", inst->id1); }
        if (inst->id2) { DPRINTF(" 2nd task # = %d\n", inst->id2); }
        if (inst->infile) { DPRINTF("input file  = \"%s\"\n", inst->infile); }
        if (inst->outfile) { DPRINTF("output file= \"%s\"\n", inst->outfile); }
    }

    if(argv) {
        for(i = 0; argv[i]; i++) {
            DPRINTF("argv[%d] == %s\n", i, argv[i]);
	}
    }
  
    DPRINTF("-----------------------\n");
}
