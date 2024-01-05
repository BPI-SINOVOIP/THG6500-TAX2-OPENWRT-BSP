#!/bin/sh

[ -z "$1" -o -z "$2" -o -z "$3" ] && exit 1
extpriv.sh "ramonitor0 create $1 $2 $3"
