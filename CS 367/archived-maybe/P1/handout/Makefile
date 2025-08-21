#-----------------------------------------------------------------------------
# Makefile
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Choose a compiler and its options
#--------------------------------------------------------------------------
CC   = gcc -std=gnu99	# Use gcc for Zeus
OPTS = -Wall -Werror -Wno-error=unused-variable -Wno-error=unused-function -pthread
DEBUG = -g # -g for GDB debugging

#--------------------------------------------------------------------
# Build Environment
#--------------------------------------------------------------------
SRCDIR=./src
OBJDIR=./obj
INCDIR=./inc
LIBDIR=./lib
BINDIR=.

#--------------------------------------------------------------------
# Build Files
#--------------------------------------------------------------------
SRCS=$(wildcard $(SRCDIR)/vm*.c)
HDRS=$(wildcard $(INCDIR)/*.h)

#--------------------------------------------------------------------
# Compiler Options
#--------------------------------------------------------------------
INCLUDE=$(addprefix -I,$(INCDIR))
LIBRARY=$(addprefix -L,$(OBJDIR))
SRCOBJS=${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}
INCS = $(wildcard $(INCDIR)/*.h)
OBJS=$(OBJDIR)/vm.o $(OBJDIR)/vm_cs.o $(OBJDIR)/vm_shell.o $(OBJDIR)/vm_support.o
OTUROBJS=$(OBJDIR)/otur_sched.o
CFLAGS=$(OPTS) $(INCLUDE) $(LIBRARY) $(DEBUG)

HELPER_TARGETS=$(BINDIR)/slow_countup $(BINDIR)/slow_door $(BINDIR)/slow_bug $(BINDIR)/slow_countdown

#--------------------------------------------------------------------
# Build Recipies for the Executables (binary)
#--------------------------------------------------------------------
TARGET = $(BINDIR)/shvm 
TARGET_LIB = $(LIBDIR)/vm_process.o

all: $(TARGET) helpers

tester: $(TARGET) $(SRCDIR)/test_otur_sched.c $(OBJDIR)/vm_support.o $(OBJDIR)/otur_sched.o
	${CC} $(CFLAGS) -o $@ $(SRCDIR)/test_otur_sched.c $(OBJDIR)/vm_support.o $(OBJDIR)/otur_sched.o

helpers: $(HELPER_TARGETS)

$(BINDIR)/slow_countup: $(OBJDIR)/slow_countup.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_countdown: $(OBJDIR)/slow_countdown.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_door: $(OBJDIR)/slow_door.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_bug: $(OBJDIR)/slow_bug.o
	${CC} ${CFLAGS} -o $@ $^  

# Links the object files to create the target binary
$(TARGET): $(OBJS) $(OTUROBJS) $(HDRS) $(INCDIR) $(OBJDIR)/libvm_sd.a
	${CC} ${CFLAGS} -o $@ $(OBJS) $(OTUROBJS) -lvm_sd

#$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c 
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	${CC} $(CFLAGS) -c -o $@ $<

#--------------------------------------------------------------------
# Cleans the binaries
#--------------------------------------------------------------------
clean:
	rm -f $(OBJS) $(SRCOBJS) $(TARGET) $(HELPER_TARGETS) tester $(OBJDIR)/*.o $(LIBDIR)/*.o
