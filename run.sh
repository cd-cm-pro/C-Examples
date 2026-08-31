#!/bin/sh
if [ ! -d "result" ]; then
    mkdir -p "result"
fi
gcc "examples/$1/main.c" -o ./result/main $2
./result/main