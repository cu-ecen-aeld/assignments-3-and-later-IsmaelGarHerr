#!/usr/bin/bash

WRITEFILE=$1
WRITESTR=$2

if [ $# -lt 2 ] 
then
     echo 'Missing arguments'
     exit 1

else
     touch "$WRITEFILE.txt" && echo "$WRITESTR" > "$WRITEFILE"

fi


