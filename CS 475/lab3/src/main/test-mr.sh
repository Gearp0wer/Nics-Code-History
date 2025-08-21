#!/bin/bash
here=$(dirname "$0")
[[ "$here" = /* ]] || here="$PWD/$here"
echo ""
cd ../mapreduce
echo "==> Part I"
go test -run Sequential 
echo ""
echo "==> Part IIA"
(cd "$here" && ./test-dgrep.sh > /dev/null)
echo ""
echo "==> Part IIB"
(cd "$here" && ./test-dgrepcount.sh > /dev/null)
echo ""
echo "==> Part III"
cd ../mapreduce
go test -run TestBasic 
echo ""
echo "==> Part IV"
go test -run Failure 
echo ""

rm  -f "$here"/mrtmp.* "$here"/diff.out "$here"/diff2.out
