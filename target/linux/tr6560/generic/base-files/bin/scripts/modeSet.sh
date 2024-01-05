#!/bin/sh
. /lib/functions/system.sh
. /lib/functions/working-mode.sh
#usage:
#       modeSet.sh bridge/router/reapter(ssid, encryption, key)/agent/controller



main()
{
    local newMode="$1"
    local ssid=$2
    local encryption=$3
    local key=$4


    # ifdown all interfaces before change working mode
    working_mode_switch_prepare
    working_mode_set_dhcp "$newMode"
    working_mode_set_network "$newMode"
    working_mode_set_prplmesh "$newMode"
    working_mode_set_wireless "$newMode" $ssid $encryption $key


    # save and apply uci
    working_mode_apply "$newMode"
}


main $1 $2 $3 $4
