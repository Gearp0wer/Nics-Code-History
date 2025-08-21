#!/bin/bash

go run dgrep.go master sequential Code pg-*.txt
if [ -s mrtmp.dgrep ]
then 
  sort -t ':' -k1,1 -k2n,2 mrtmp.dgrep | diff - dgrep-test1-out.txt > diff.out
else
  echo "Failed test 1" > /dev/stderr
  exit
fi
if [ -s diff.out ]
then
echo "Failed test 1. Output should be as in dgrep-test1-out.txt. Your output differs as follows (from diff.out):" > /dev/stderr
  cat diff.out
else
  echo "Passed test 1" > /dev/stderr
fi

go run dgrep.go master sequential "[Mmvf]aster" pg-*.txt
if [ -s mrtmp.dgrep ]
then
   sort -t ':' -k1,1 -k2n,2 mrtmp.dgrep | diff - dgrep-test2-out.txt > diff2.out
else
  echo "Failed test 2" > /dev/stderr
  exit
fi
if [ -s diff2.out ]
then
echo "Failed test 2. Output should be as in dgrep-test2-out.txt. Your output differs as follows (from diff2.out):" > /dev/stderr
  cat diff2.out
else
  echo "Passed test 2" > /dev/stderr
fi


