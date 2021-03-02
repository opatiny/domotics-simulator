#!/bin/bash

C_FILES=`find . -mindepth 2 -name "*.c"`

if gcc -g $C_FILES ./main.c -lm -o ./main.out ; then
    ./main.out
else
    echo "Compilation failed!"
fi
