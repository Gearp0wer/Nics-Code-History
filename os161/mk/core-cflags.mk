# Contains CFLAGS that are used in every part of the kernel.
# Instead of redundantly specifying these in each makefile,
# they are implemented here.

# Set C version that we use.
# We use some GNU C extensions, so use gnu99 instead of c99 for
# clarity / correctness.
CFLAGS +=-std=gnu99

# Don't use the standard library header files.
CFLAGS +=-nostdinc

# We aren't writing the kernel in a position-independent way.
CFLAGS +=-mno-abicalls -fno-pic

# Warning flags.
CFLAGS +=-Wall -Wextra -Wwrite-strings -Werror

# Don't error on unused variables or parameters.
CFLAGS +=-Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=unused-function

# Includes needed by every part of the tree.
CFLAGS +=-I$(OSTREE)/include -I$(OSTREE)/kern/include -I$(OSTREE)/kern/compile 

# Enable debugging symbols, so that we can debug properly in gdb.
CFLAGS +=-g

# We don't have access to an existing stdlib -- only our own libc
# in lib/libc.
LDFLAGS +=-nostdlib