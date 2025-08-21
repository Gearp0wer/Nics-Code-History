#!/bin/bash

# Shell script used to create a submission for your project.
#
# WARNING: This script will run "make clean" on your source tree.
# This should be fine, but if your compilation is in a weird state,
# it is possible that something will go wrong.
#
# But, importantly: If your code does not compile after a "make clean",
# then your grader would already have been unable to compile it.
#
# So, be sure your code can clean build!

# Check that we're in the right directory.
if ! ( [ -d kern ] && [ -d lib ] && [ -d man ] && [ -d mk ] ); then
    echo $(tput setaf 1)ERROR: $(tput sgr0)$0 was called from the wrong directory.
    echo "Usage: ./submit.sh"
    echo "       i.e. if you're not calling it as ./submit.sh, you're in the wrong directory."
    exit 1
fi

make clean

rm -f submission.DOESNOTCOMPILE.tar
rm -f submission.DOESNOTCOMPILE.tar.gz
rm -f submission.tar.gz

touch submission.DOESNOTCOMPILE.tar

# Collect files (includes hidden directories)
for file in `ls -A -1`; do
    # Skip the submission file itself
    if [ "submission.DOESNOTCOMPILE.tar" != "$file" ]; then
        # Just show each directory being tarred, instead of tar -v
        echo "TAR     $file"
        # Add each file to the tar file. Use --transform to put them all
        # inside a "os161/" directory.
        tar rf submission.DOESNOTCOMPILE.tar --transform 's,^,os161/,' "$file"
    fi
done

# Gzip the submission
gzip submission.DOESNOTCOMPILE.tar

# Finally, rebuild the kernel to ensure that it compiles.
if make -j8; then
    mv -f submission.DOESNOTCOMPILE.tar.gz submission.tar.gz
    echo "$(tput setaf 2)-----------------------------------------------------------------------$(tput sgr0)"
    echo "$(tput setaf 2)Success: $(tput sgr0)Kernel clean build has no errors."
    echo ""
    echo "         Your submission file has been saved to 'submission.tar.gz.'"
    echo "         Please rename it as appropriate, then submit it!"
    echo "$(tput setaf 2)-----------------------------------------------------------------------$(tput sgr0)"
else
    echo "$(tput setaf 1)-------------------------------------------------------------------------------------$(tput sgr0)"
    echo "$(tput setaf 1)Failure: $(tput sgr0)Kernel clean build encountered an error."
    echo ""
    echo "         Your submission file has been saved to 'submission.DOESNOTCOMPILE.tar.gz.'"
    echo ""
    echo "         You may still submit it, but if your code does not compile, you will"
    echo "         not score many points on the project (check your rubric for details)."
    echo ""
    echo "         Please double check the compiler output and be sure to fix any errors."
    echo "$(tput setaf 1)-------------------------------------------------------------------------------------$(tput sgr0)"
fi