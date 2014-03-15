#!/bin/bash
# auxiliar del makefile, reporta tiempo usado

TIME_FILE="$1" ; shift
NAME="$1" ; shift

TIME_TAKEN=$(/usr/bin/time -a -o /dev/stdout -f "%e" "$@" | tr '\n' ' ')
echo "$TIME_TAKEN $NAME" >> "$TIME_FILE"
