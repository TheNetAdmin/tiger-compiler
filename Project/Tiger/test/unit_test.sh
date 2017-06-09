#!/bin/bash

PWD=$(pwd)
TEST_ARG='-'
TEST_BIN=$PWD/test

function test(){
    filename=$PWD/testcase/$1
    # echo -ne "Test for "$filename"\t"
    cat "$filename" | $TEST_BIN - 1>/dev/zero 2>test.err
    if [ -s test.err ];
    then
        # echo " FAILED"
        return 1
    else
        # echo " PASSED"
        return 0
    fi
}

echo "---- UNIT TEST FOR TIGER COMPILER ----"
for test_case in `ls $PWD/testcase`
do
    test $test_case
    if [ $? != 0 ];
    then
        echo -e "== Test failed for [" $test_case "]\tFAILED =="
        # cat test.err >$test_case.err
        cat $PWD/test.err
    fi
done
rm -f test.err
echo "---- UNIT TEST FOR TIGER COMPILER COMPLETE ----"