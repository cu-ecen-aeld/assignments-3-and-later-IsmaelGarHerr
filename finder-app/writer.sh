#!/usr/bin/bash

WRITEFILE=$1
WRITESTR=$2
IFS='/'

if [ $# -lt 2 ] 
then
     echo "Missing Argument, please  try again with valid inputs"
     exit 1

else
     read -ra array <<< "$WRITEFILE"
     ARRAYSIZE=${#array[@]}
     FILENAME=${array[${ARRAYSIZE}-1]}
     FILEPATH=${WRITEFILE:1:(${#WRITEFILE}-${#FILENAME}-1)}
     mkdir -p "/${FILEPATH}"
     cd "/${FILEPATH}" || exit 1
     if [ -e "${FILENAME}" ]
     then
        rm "${FILENAME}"
     fi 
     touch "${FILENAME}" && echo "${WRITESTR}" > "${FILENAME}"
     echo "New ${FILENAME} file created in /${FILEPATH}"   
fi

