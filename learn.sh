#!/bin/bash

loop=0

while [ 1 = 1 ]
do

    let "loop = loop + 1"
    ./prog
    git add "save.txt"
    git commit -m "Learn $loop"

done
