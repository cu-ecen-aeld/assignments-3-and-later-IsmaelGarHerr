#!/usr/bin/bash

WRITEFILE=$1
WRITESTR=$2
IFS="/"

if [ $# -lt 2 ] 
then
     echo "Missing Argument, please  try again with valid inputs"
     exit 1

else
     read -ra array <<< "$WRITEFILE"
     ARRAYSIZE=${#array[@]}
     FILENAME=${array[ARRAYSIZE]}
     PATH=${WRITESTR:0:((${#WRITESTR})-(${#FILENAME}))}

     mkdir -p "${PATH}"
     cd "${PATH}" || exit 1

     if [ -e "${FILENAME}" ]
     then
        rm "${FILENAME}"
     fi 
     touch "${FILENAME}" && echo "${WRITESTR}" > "${FILENAME}"
     echo "New ${FILENAME} file created in ${PATH}"   
fi


