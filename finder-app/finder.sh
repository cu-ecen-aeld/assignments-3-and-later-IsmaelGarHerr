#!/bin/bash

FILEDIR=$1
SRCHSTR=$2

if [ $# -lt 2 ]
then
    echo "Missing Argument, please  try again with valid inputs"
    exit 1
    
else
    echo "Looking for file ${SRCHSTR}"
    cd "$FILEDIR" || ( echo "${FILEDIR} is not a valid directory" && exit 1 )
    FILECOUNT=$( find ./ -type f | wc -l)
    STRCOUNT=$( grep -R "$SRCHSTR" | wc -l)

    echo "The number of files are ${FILECOUNT}  and the number of matching lines are ${STRCOUNT} "
    
fi
