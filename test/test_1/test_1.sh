#!/bin/bash

echo "Running tests..."
echo "================="

PASS=true
testparentdir="./test_1"

for testdir in $testparentdir/case_*; do

    if [[ ! -d "$testdir" ]]; then
        continue
    fi

    echo "Test: $testdir"
    echo "Testing encode mode with single error"

    # copy input.txt from case folder to current folder
    cp $testdir/input.txt .

    # no need for stdin and stdout as the script automatically takes input.txt and produce output.txt
    ./solution 0 0

    if diff -q output.txt "$testdir/output.txt" > /dev/null; then
        echo "PASS"
    else
        echo "FAIL"
        echo "Expected:"
        cat "$testdir/output.txt"
        echo "Got:"
        cat output.txt
        PASS=false
        break
    fi

    echo
done

rm -f input.txt
rm -f output.txt
rm -f encoded.txt
rm -f errorized.txt

if $PASS; then
    echo "All tests passed!"
    exit 0
else
    echo "Some tests failed."
    exit 1
fi
