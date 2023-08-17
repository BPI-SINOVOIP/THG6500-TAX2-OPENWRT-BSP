#!/bin/sh

if ( ! grep -qs '^root:[!x]\?:' /etc/shadow || ! grep -qs '^root:[!x]\?:' /etc/passwd ) && \
	[ -z "$FAILSAFE" ]
then
	echo "WARNING: telnet is a security risk"
	busybox login
else
	exec /bin/ash --login
fi
