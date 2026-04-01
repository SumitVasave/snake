#!/bin/bash

gcc -o program cur.c -lncurses

if (( $?==0 )); then
./program
else
exit 1
fi
