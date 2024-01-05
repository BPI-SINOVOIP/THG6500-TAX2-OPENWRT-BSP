#!/bin/sh

[ -z "$1" -o -z "$2" -o -z "$3" ] && exit 1

ramonitor="ramonitor0"
if [ "$3" = "5g" -a ! -f "/lib/wifi/dbac.sh" ]; then
    ramonitor="ramonitor1"
fi

extpriv.sh "$ramonitor create $1 $2"
