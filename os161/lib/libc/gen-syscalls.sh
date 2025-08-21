# Take the PLATFORM name as the first argument, and CALLNO_H
# as the second argument
if [ -z "${1}" ] || [ -z "${2}" ]; then
    echo "Usage: $0 <PLATFORM> <CALLNO_H>"
    exit 1
fi

# We need to use a temporary file for generating syscalls.S.
# This is because libc could in theory be compiled by several
# userspace programs simultaneously, with each one trying to generate
# the syscalls.S file.
#
# If they're all writing to the same tmp file, then things go wrong,
# because the file has too many copies of the output and doesn't compile.
TMPFILE=$(mktemp)

echo "/* Automatically generated from syscalls-$1.S */" \
    > $TMPFILE
cat syscalls-$1.S >> $TMPFILE

# Parse the callno.h file based on the second argument
./callno-parse.sh < $2 >> $TMPFILE
mv -f $TMPFILE syscalls.S

# If something went wrong... then the next step should fail anyways.
true