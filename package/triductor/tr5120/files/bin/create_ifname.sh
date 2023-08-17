#!/bin/sh

ramonitor="ramonitor0"
if [ "$2" = "5g" -a ! -f "/lib/wifi/dbac.sh" ]; then
    ramonitor="ramonitor1"
fi

extpriv.sh "$ramonitor create $1 ap"