#-----------------------------------------------------------------------------
# Makefile
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Choose a compiler and its options
#--------------------------------------------------------------------------
CC   = gcc -std=gnu99	# Use gcc for Zeus
OPTS = -Og -Wall -Werror -Wno-error=unused-variable -Wno-error=unused-function -pthread
DEBUG = -g					# -g for GDB debugging

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
OBJS=$(OBJDIR)/vm.o $(OBJDIR)/vm_cs.o $(OBJDIR)/vm_shell.o $(OBJDIR)/op_sched.o $(OBJDIR)/vm_support.o
CFLAGS=$(OPTS) $(INCLUDE) $(LIBRARY) $(DEBUG)

HELPER_TARGETS=$(BINDIR)/slow_cooker $(BINDIR)/slow_hat $(BINDIR)/slow_bug $(BINDIR)/slow_printer

#--------------------------------------------------------------------
# Build Recipies for the Executables (binary)
#--------------------------------------------------------------------
TARGET = $(BINDIR)/vm 

all: $(TARGET) helpers

tester: $(TARGET) $(SRCDIR)/test_op_sched.c $(OBJDIR)/vm_support.o $(OBJDIR)/op_sched.o
	${CC} $(CFLAGS) -o $@ $(SRCDIR)/test_op_sched.c $(OBJDIR)/vm_support.o $(OBJDIR)/op_sched.o

helpers: $(HELPER_TARGETS)

$(BINDIR)/slow_cooker: $(OBJDIR)/slow_cooker.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_printer: $(OBJDIR)/slow_printer.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_hat: $(OBJDIR)/slow_hat.o
	${CC} ${CFLAGS} -o $@ $^

$(BINDIR)/slow_bug: $(OBJDIR)/slow_bug.o
	${CC} ${CFLAGS} -o $@ $^  

# Links the object files to create the target binary
$(TARGET): $(OBJS) $(HDRS) $(INCDIR)
	${CC} ${CFLAGS} -o $@ $(OBJS) -lvm_sd

#$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c 
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/vm_settings.h					 
	${CC} $(CFLAGS) -c -o $@ $<

#--------------------------------------------------------------------
# Cleans the binaries
#--------------------------------------------------------------------
clean:
	rm -f $(OBJS) $(SRCOBJS) $(TARGET) $(HELPER_TARGETS) tester $(OBJDIR)/*.o $(LIBDIR)/*.o
