#!/bin/bash

# This script automates the process of copying specific files from the shared
# directory (/usr/local/shared/cs471/PA1/) into the appropriate directories 
# within the os161 project structure. Run this script to set up the files for
# the assignment (PA1). 
# You must copy these files accurately BEFORE you start coding the solution.

# Make sure the directory has the structure that we expect
if ! ( [ -d kern ] && [ -d lib ] && [ -d man ] && [ -d mk ] ); then
    echo "ERROR: update_files.sh is not running inside an OS/161 source directory"
    echo "Please make sure you're running it as ./update_files.sh inside e.g. ~/os161"
    exit 1
fi

# Ensure that any failed copy prints an error and stops the script
set -e

# Copy files from the shared directory to the appropriate locations
cp /usr/local/shared/cs471/PA1/stoplight.c kern/asst1/
cp /usr/local/shared/cs471/PA1/stoplight_framework.h kern/asst1/
cp /usr/local/shared/cs471/PA1/stoplight_framework.c kern/asst1/
cp /usr/local/shared/cs471/PA1/core-cflags.mk mk/
cp /usr/local/shared/cs471/PA1/stoplight-check .
cp /usr/local/shared/cs471/PA1/stoplight-timeout .
cp /usr/local/shared/cs471/PA1/stoplight-test.sh .

# Print a success message
echo "Successfully copied all files!"
