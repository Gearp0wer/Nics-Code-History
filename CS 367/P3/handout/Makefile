#-----------------------------------------------------------------------------
# Makefile
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Choose a compiler and its options
#--------------------------------------------------------------------------
CC   = gcc -std=gnu99	# Use gcc for Zeus
OPTS = -Og -Wall -Werror -Wno-error=unused-variable -Wno-error=unused-function
DEBUG = -g					# -g for GDB debugging

#--------------------------------------------------------------------
# Build Environment
#--------------------------------------------------------------------
UID := $(shell id -u)
SRCDIR=./src
OBJDIR=./obj
INCDIR=./inc
BINDIR=.

#--------------------------------------------------------------------
# Build Files
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# Compiler Options
#--------------------------------------------------------------------
INCLUDE=$(addprefix -I,$(INCDIR))
HEADERS=$(wildcard $(INCDIR)/*.h)
CFLAGS=$(OPTS) $(INCLUDE) $(DEBUG)
OBJECTS=$(addprefix $(OBJDIR)/,anav.o logging.o parse.o util.o)

#--------------------------------------------------------------------
# Build Recipies for the Executables (binary)
#--------------------------------------------------------------------
all: anav my_pause slow_cooker my_echo

anav: $(OBJECTS) 
	$(CC) $(CFLAGS) -o $@ $^
#	gcc -Wall -std=gnu11 -o anav anav.o logging.o parse.o util.o

$(OBJDIR)/anav.o: $(SRCDIR)/anav.c $(INCDIR)/anav.h
	$(CC) -c $(CFLAGS) -o $@ $<
#	gcc -Wall -g -std=gnu11 -c anav.c   
#	gcc -D_POSIX_C_SOURCE -Wall -g -std=c99 -c anav.c   

$(OBJDIR)/parse.o: $(SRCDIR)/parse.c $(INCDIR)/parse.h
	$(CC) -c $(CFLAGS) -o $@ $<
#	gcc -Wall -g -std=c99 -c parse.c     

$(OBJDIR)/util.o: $(SRCDIR)/util.c $(INCDIR)/util.h
	$(CC) -c $(CFLAGS) -o $@ $<
#	gcc -Wall -g -std=c99 -c util.c     

$(OBJDIR)/logging.o: $(SRCDIR)/logging.c $(INCDIR)/logging.h
	$(CC) -c $(CFLAGS) -Wformat-truncation=0 -o $@ $<
#	gcc -Wall -Wformat-truncation=0 -g -std=c99 -c logging.c     

my_pause: $(SRCDIR)/my_pause.c
	$(CC) $(CFLAGS) -o $@ $^
#	gcc -D_POSIX_C_SOURCE -Wall -Og -std=c99 -o my_pause my_pause.c

slow_cooker: $(SRCDIR)/slow_cooker.c
	$(CC) $(CFLAGS) -o $@ $^
#	gcc -D_POSIX_C_SOURCE -Wall -Og -std=c99 -o slow_cooker slow_cooker.c

my_echo: $(SRCDIR)/my_echo.c
	$(CC) $(CFLAGS) -o $@ $^
#	gcc -D_POSIX_C_SOURCE -Wall -Og -std=c99 -o my_echo my_echo.c

clean:
	rm -rf $(OBJDIR)/*.o anav my_pause slow_cooker my_echo




