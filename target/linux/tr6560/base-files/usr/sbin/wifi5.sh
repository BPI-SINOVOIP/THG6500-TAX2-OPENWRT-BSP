#!/bin/sh

usage() {
	cat <<EOF
Usage: $0 [enable|disable]
enables or disables wifi5.
EOF
	exit 1
}

change_to_wifi5()
{
	local ifname=$1
	local file=$2

	sed -i '/ieee80211ax/d' $file
	sed -i '/he_/d' $file
	sed -i '/bss=/,$d' $file

	local bssid=`grep "bssid=" $file | head -n 1 | awk -F '=' '{print $2}'`
	[ -n "$bssid" ] && {
		local oIFS="$IFS"; IFS=":"; set -- $bssid; IFS="$oIFS"
		mac_part4=$(echo "$4" | cut -c2-3)$(echo "$4" | cut -c1-1)
		sed -i "s/^bssid=.*/bssid=$1:$2:$3:${mac_part4}:$5:$6/" $file
	}

	sed -i "s/^interface=.*/interface=$ifname/" $file
	sed -i '/^ssid=/s/$/_WiFi5/' $file
}

create_ifname()
{
	local phy=$1
	local ifname=$2

	[ "$phy" = "phy0" ] && create_ifname.sh "$ifname" "ap" "2g" || create_ifname.sh "$ifname" "ap" "5g"

	auto_channel=`uci get wireless.radio${phy#phy}.channel`
	[ "$auto_channel" = "auto" ] && extpriv.sh "$ifname acs sw 1" || extpriv.sh "$ifname acs sw 0"
}

_wifi5_enable()
{
	local phy=$1

	[ -f "/var/run/hostapd-${phy}.conf" -a -n "$(grep ieee80211ax /var/run/hostapd-${phy}.conf)" ] && {
		local ifname="wlan${phy#phy}-wifi5"
		cp /var/run/hostapd-${phy}.conf /var/run/hostapd-${phy}-wifi5.conf
		change_to_wifi5 $ifname /var/run/hostapd-${phy}-wifi5.conf
		create_ifname $phy $ifname
		ubus call hostapd config_add "{\"iface\":\"$ifname\",\"config\":\"/var/run/hostapd-${phy}-wifi5.conf\"}" >/dev/null 2>&1
	}
}

_wifi5_disable()
{
	local phy=$1

	[ -f "/var/run/hostapd-${phy}-wifi5.conf" ] && {
		local ifname="wlan${phy#phy}-wifi5"
		ubus call hostapd config_remove "{\"iface\":\"$ifname\"}"
		ip link set dev "$ifname" down 2>/dev/null
		iw dev "$ifname" del
	}
}

_wifi5()
{
	[ -n "$2" ] && phy_list="$2" || phy_list="phy0 phy1"

	for phy in $phy_list; do
		[ enable = "$1" ] && _wifi5_enable $phy || _wifi5_disable $phy
	done
}

wifi5()
{
	[ enable = "$1" ] && _wifi5 disable $2

	_wifi5 "$@"
}

case "$1" in
	enable) wifi5 "enable" $2;;
	disable) wifi5 "disable" $2;;
	*) usage; exit 1;;
esac