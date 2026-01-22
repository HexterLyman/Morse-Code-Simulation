#!/bin/bash

echo "Running tests..."
echo "================="

PASS=true
testparentdir="./test_5"

for testdir in $testparentdir/case_*; do

    if [[ ! -d "$testdir" ]]; then
        continue
    fi
    
    echo "Test: $testdir"
    echo "Testing invalid encode / decode"

    # copy input.txt from case folder to current folder
    cp $testdir/input.txt .

    # no need for stdin and stdout as the script automatically takes input.txt and produce output.txt
    ./solution 5 0 > output.tmp

    if diff -q output.tmp "$testdir/output.txt" > /dev/null; then
        echo "PASS"
    else
        echo "FAIL"
        echo "Expected:"
        cat "$testdir/output.txt"
        echo "Got:"
        cat output.tmp
        PASS=false
        break
    fi

    echo
done

rm -f input.txt
rm -f output.txt
rm -f encoded.txt
rm -f errorized.txt
rm -f output.tmp

if $PASS; then
    echo "All tests passed!"
    exit 0
else
    echo "Some tests failed."
    exit 1
fi
