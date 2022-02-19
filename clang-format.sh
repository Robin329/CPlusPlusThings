#!/bin/bash

find . -path '*.cpp' -o -path '*.h' ! -name '*.h' > ./list.txt

while read line
do
    echo $line
    clang-format -style=file -i $line
done < list.txt

rm -rf ./list.txt
