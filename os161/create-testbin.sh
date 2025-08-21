#!/bin/bash

# Helper script to create new "testbin" executables.
#
# This creates a new directory under testbin with the following contents:
# - <testbin name>.c -- the source file for your new testbin
# - Makefile         -- the Makefile for your new testbin (important: it includes mk/build-testbin.mk)
# - .gitignore       -- a .gitignore file ignoring the new executable
#
# Note that the new testbin will automatically be picked up by the Makefile --
# so after creating it, you just need to 'make' again to build and install it.

if ! ( [ -d kern ] && [ -d lib ] && [ -d man ] && [ -d mk ] ); then
    echo $(tput setaf 1)ERROR: $(tput sgr0)$0 was called from the wrong directory.
    echo "Usage: ./create-testbin <new testibn name>"
    echo "       i.e. if you're not calling it as ./create-testbin, you're in the wrong directory."
    exit 1
fi

if [ "x$1" = x ]; then
    echo "Usage: $0 <new testbin name>"
    exit 1
fi

TESTBIN_NAME="$1"

if [ -d "testbin/$TESTBIN_NAME" ]; then
    echo "$(tput setaf 1)ERROR: $(tput sgr0)a testbin called '$TESTBIN_NAME' already exists."
    exit 1
fi

# Create the new directory
mkdir -p "testbin/$TESTBIN_NAME"

# Create the new source file
cat > "testbin/$TESTBIN_NAME/$TESTBIN_NAME.c" <<- EOM
/*
 * $TESTBIN_NAME - does something. (You decide!)
 */

/* Include some standard headers (add more as needed) */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int
main(int argc, char **argv) {
    /* Your code here... */
    printf("Hello, world!\n");
}
EOM

# Create the Makefile
cat > "testbin/$TESTBIN_NAME/Makefile" <<- EOM
# Makefile for $TESTBIN_NAME

SRCS-y=$TESTBIN_NAME.c
TARGET_NAME=$TESTBIN_NAME

include ../../mk/build-testbin.mk
EOM

# Create the .gitignore
cat > "testbin/$TESTBIN_NAME/.gitignore" <<- EOM
# Ignore the compiled executable for each testbin
$TESTBIN_NAME
EOM

echo "$(tput setaf 2)------------------------------------------------------------------------$(tput sgr0)"
echo "$(tput setaf 2)Success: $(tput sgr0)New test program '$TESTBIN_NAME' created."
echo ""
echo "         Now you can run 'make' to build and install it."
echo "$(tput setaf 2)------------------------------------------------------------------------$(tput sgr0)"