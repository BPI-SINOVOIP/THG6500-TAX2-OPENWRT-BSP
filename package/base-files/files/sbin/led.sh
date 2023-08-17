#!/bin/sh
# (C) 2008 openwrt.org

. /lib/functions.sh
ACTION=$1
NAME=$2
DELAY_ON=$3
DELAY_OFF=$4
do_led() {
	local name
	local sysfs

	config_get sysfs $1 sysfs
	if [ "$NAME" != "all" ]; then
		config_get name $1 name
		[ "$name" = "$NAME" -o "$sysfs" = "$NAME" -a -e "/sys/class/leds/${sysfs}" ] && {
			if [ "$ACTION" = "set" ]; then
				echo none >/sys/class/leds/${sysfs}/trigger
				echo 1 >/sys/class/leds/${sysfs}/brightness
			elif [ "$ACTION" = "clear" ]; then
				echo none >/sys/class/leds/${sysfs}/trigger
				echo 0 >/sys/class/leds/${sysfs}/brightness
			else
				echo timer >/sys/class/leds/${sysfs}/trigger
				[ -n "${DELAY_ON}" ] &&{
					echo ${DELAY_ON} >/sys/class/leds/${sysfs}/delay_on
				}
				[ -n "${DELAY_OFF}" ] &&{
					echo ${DELAY_OFF} >/sys/class/leds/${sysfs}/delay_off
				}
			fi
			exit 0
		}
	else
		[ -n "$sysfs" -a -e "/sys/class/leds/${sysfs}" ] && {
			[ "$ACTION" = "set" ] &&
				echo 1 >/sys/class/leds/${sysfs}/brightness \
				|| echo 0 >/sys/class/leds/${sysfs}/brightness
		}
	fi
}

[ "$1" = "clear" -o "$1" = "set" -o "$1" = "blink" ] &&
	[ -n "$2" ] &&{
		config_load system
		config_foreach do_led
		exit 1
	}
