#!/bin/bash

gcc -o game snake.c -lncurses

if (($?==0)); then
    echo "The Game has been compiled ; do ./game to run it."
    echo "Move with arrow keys."
    echo "And q to quit."
else
    echo "Some ERROR occurred."
fi
