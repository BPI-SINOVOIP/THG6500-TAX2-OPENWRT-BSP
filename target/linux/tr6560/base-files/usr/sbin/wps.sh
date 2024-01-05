#!/bin/sh
. /usr/sbin/wps_led.sh

usage() {
	cat <<EOF
Usage: $0 [MAC] [start|ok|fail]
wps status.
EOF
	exit 1
}

get_radio()
{
    string=`uci show wireless | grep "device=" | awk '{split($0,arr,".");print arr[2] }'`

    for iRadio_node in $string; do
        ifname=`uci -q get wireless.$iRadio_node.ifname`
        [ -z "$ifname" ] && ifname=`uci -q -P /var/state get wireless.$iRadio_node.ifname`
        [ "$ifname" = "$1" ] && {
            radio=`uci -q get wireless.$iRadio_node.device`
            return
        }
    done
}

# 获取mac地址对应的接口名称
ifname=`ifconfig | grep -i $1 | awk '{print $1}'`
[ -z "$ifname" ] && exit 1

# 获取ifname对应的radio
get_radio $ifname
[ -z "$radio" ] && exit 1
phy=${radio#radio}

# 配置新wps状态
ubus call hotplug.hostapd call "{'env':['ACTION=wps_status','PHY=${phy}','WPS_STATUS=$2']}"

case "$2" in
    "start")
        led blink
    ;;
    "ok")
        led on
    ;;
    "fail")
        [ "$radio" = "radio0" ] && other_band_wps=`uci -q -P /var/state get wireless._phy1.wps_status` || other_band_wps=`uci -q -P /var/state get wireless._phy0.wps_status`
        [ -z "$other_band_wps" -o "$other_band_wps" = "start" ] && {
            wps_led=`ubus call uci get '{"config":"system","section":"led_wps","option":"sysfs"}' | jsonfilter -e "@.value"`
            ubus call hotplug.led call "{'env':['ACTION=led_end','LED=$wps_led']}"
        }
    ;;
    *) usage; exit 1;;
esac
