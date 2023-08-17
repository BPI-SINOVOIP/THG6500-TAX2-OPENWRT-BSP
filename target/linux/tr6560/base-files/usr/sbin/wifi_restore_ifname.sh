#!/bin/sh

string=`uci show wireless | grep "device=" | awk '{split($0,arr,".");print arr[2] }'`

for iRadio_node in $string; do
    ifname=`uci -q get wireless.$iRadio_node.ifname`
    if [ "$ifname" = "wlan0-ap" ]; then
        uci set wireless.$iRadio_node.ifname='wlan0'
    elif [ "$ifname" = "wlan1-ap" ]; then
        uci set wireless.$iRadio_node.ifname='wlan1'
    fi
done
wifi up
uci commit