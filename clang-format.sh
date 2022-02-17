#!/bin/bash
while read line
do
    echo $line
    clang-format -style=file -i $line
done < list.txt
