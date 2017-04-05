#! /bin/bash

# flex
flex WordCount.l

# c compile
gcc lex.yy.c -o count

# test
cat test.txt | ./count
