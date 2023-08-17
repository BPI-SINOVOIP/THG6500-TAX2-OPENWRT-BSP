#!/bin/sh

. /lib/functions.sh

do_set_dhcpc() {
	proto=`uci -q get network.lan.proto`
	if [ -n "$proto" -a "$proto" = "static" ]; then
		uci set network.lan.proto='dhcp'
		uci commit
		ubus call service event "{ \"type\": \"config.change\", \"data\": { \"package\": \"$(basename /var/run/config.check/network)\" }}"
	fi
}

do_set_dhcpc
exit 0
