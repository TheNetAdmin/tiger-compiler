#!/bin/bash
pwd=$(pwd)
test_path=$pwd/testcase
filename=$test_path/test$1.tig
echo "Testing "$filename
cat "$filename" | ./test - >test.log 2>&1
