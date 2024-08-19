#!/usr/bin/bash

WRITEFILE=$1
WRITESTR=$2
IFS="/"

if [ $# -lt 2 ] 
then
     echo 'Missing arguments'
     exit 1

else
     read -ra array <<< "$WRITEFILE"
     SIZE=${#array[@]}
     for (( i=0; i<="$SIZE"; i+=1 ))
     do
        if [ "$i" -eq "$SIZE" ]
        then
            touch "${array[$i]}"
        else
            mkdir "${array[$i]}"
            cd "${array[$i]}" || exit 1
        fi
     done
     touch "$WRITEFILE" || exit 1
     echo "$WRITESTR" > "$WRITEFILE" 

fi


