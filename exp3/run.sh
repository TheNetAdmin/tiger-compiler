#! /bin/bash
bison calculator.y
gcc calculator.tab.c -lm
./a.out < input.txt
