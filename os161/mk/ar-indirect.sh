#!/bin/bash
# A helper script for creating archives in a parallelism-safe way.
# That is, normally, if you have three makefiles all trying to do:
#
#   ar -cru thing.a obj.o obj2.o
#
# at the same time, you will get a broken archive.
#
# This is mostly to try to mitigate problems if more than one job is
# trying to create an archive at once, but this is really not officially
# supported. Just run make -j8 at the top of the source tree for
# correct multithreaded compilation.
#
# So, we "simply" create a new archive every time, using a $(mktemp)
# file.

AR=$1

# Move the arguments over
shift

REAL_OUTPUT=$1

# Move the arguments over so we can ar them together
shift

# Get a temporary file: Add .a so that ar doesn't complain
TMPFILE="$(mktemp -u).a"

"$AR" -cru $TMPFILE "$@" || exit 1

# Create the new file.
mv -f $TMPFILE $REAL_OUTPUT