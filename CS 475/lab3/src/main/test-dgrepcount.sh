#!/bin/bash
go run dgrepcount.go master sequential red pg-*.txt
if [ -s mrtmp.dgrepcount ]
then
  diff mrtmp.dgrepcount dgrepcount-test1-out.txt > diff.out
else
  echo "Failed test 1" > /dev/stderr
  exit
fi
if [ -s diff.out ]
then
echo "Failed test 1. Output should be as in dgrepcount-test1-out.txt. Your output differs as follows (from diff.out):" > /dev/stderr
  cat diff.out
  exit
else
  echo "Passed test 1" > /dev/stderr
fi

go run dgrepcount.go master sequential "t[wo]o" pg-*.txt
if [ -s mrtmp.dgrepcount ]
then
   diff mrtmp.dgrepcount dgrepcount-test2-out.txt > diff2.out
else
   echo "Failed test 2" > /dev/stderr
   exit
fi  
if [ -s diff2.out ]
then
  echo "Failed test 2. Output should be as in dgrepcount-test2-out.txt. Your output differs as follows (from diff2.out):" > /dev/stderr
  cat diff2.out
else
  echo "Passed test 2" > /dev/stderr
fi


