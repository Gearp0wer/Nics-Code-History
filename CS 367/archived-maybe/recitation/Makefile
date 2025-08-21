# comments are always a great idea.

# we use this variable as $(CC) when building commands.
CC=gcc

# we keep using these flags in combination, so they're
# stuffed into a variable. Saves us from having to 
# re-type them repeatedly, and of course we can then
# change it in one place for all uses.
CFLAGS=-O0 -std=c99

FUNC_OS=dot4.o call_dot4.o scale.o call_scale.o call_sum.o intermediate.o rec_fib.o 

# see below for the rec12 target.
all: rec12

# the command 'make clean' should remove all generated files.
clean:
	-rm -rf *~ *# $(FUNC_OS) rec12.s rec12.o rec12

# target rec12 builds the overall executable, rec12.
# depends on all the individual functions' object files.
rec12: rec12.o  $(FUNC_OS) support_funcs.o
	$(CC) $(CFLAGS) -o rec12 rec12.o $(FUNC_OS) support_funcs.o

# compiles rec12.c into rec12.s; needs no other files.
rec12.s: rec12.c
	$(CC) $(CFLAGS) -S rec12.c

# compiles rec12.s into rec12.o; needs no other files.
rec12.o: rec12.s
	$(CC) $(CFLAGS) -c rec12.s

# each of the remaining targets also compiles each
# .s file into the corresponding .o file, with no
# other dependencies on other files.

call_dot4.o: call_dot4.s
	$(CC) $(CFLAGS) -c call_dot4.s

dot4.o: dot4.s
	$(CC) $(CFLAGS) -c dot4.s

scale.o: scale.s
	$(CC) $(CFLAGS) -c scale.s

call_scale.o: call_scale.s
	$(CC) $(CFLAGS) -c call_scale.s

call_sum.o: call_sum.s
	$(CC) $(CFLAGS) -c call_sum.s

intermediate.o: intermediate.s
	$(CC) $(CFLAGS) -c intermediate.s

rec_fib.o: rec_fib.s
	$(CC) $(CFLAGS) -c rec_fib.s
