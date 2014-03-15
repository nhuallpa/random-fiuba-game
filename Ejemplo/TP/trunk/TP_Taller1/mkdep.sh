#!/bin/sh
# auxiliar del makefile, extiende el archivo de dependencias para tolerar borrado de fuentes

DEP_FILE="$1" ; shift

TEMP_FILE="$DEP_FILE".tmp

"$@"
cp "$DEP_FILE" "$TEMP_FILE"
sed -e 's/^[^:]*://' -e 's/\\$//' < "$TEMP_FILE" | fmt -1 | sed -e 's/^[[:space:]]*//' -e 's/$/:/' >> "$DEP_FILE"
rm -f "$TEMP_FILE"
