#!/bin/sh
if [ ! -d "result" ]; then
    mkdir -p "result"
fi
gcc "examples/$1/main.c" -o ./result/main $1
./result/main