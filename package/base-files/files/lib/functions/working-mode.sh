check_working_mode()
{
    local newMode=$1
    local ret=0

    case $newMode in
        'router'|'bridge'|'repeater'|'agent'|'controller')
            ;;
        *)
            logger -t working-mode -s "invalid newMode=${newMode}"
            ret=-1
            ;;
    esac

    return $ret
}


working_mode_switch_prepare()
{
    local downIfList="wan wan6 wwan agent"
    local disabled=''

    for interface in $downIfList; do
        disabled=`uci -q get network.$interface.disabled`
        if [ -n "$disabled" -a "$disabled" = 1 ]; then
            continue
        fi

        ifdown $interface
        sleep 1
    done
}



# description: change dhcp config according to working mode
# input: $1 - new mode, "router"/"bridge"/"repeater"/"agent"/"controller"
working_mode_set_dhcp()
{
    local newMode=$1

    `check_working_mode $newMode`
    if [ $? -ne 0 ]; then
        return -1
    fi

    if [ "$newMode" = 'router' -o "$newMode" = "controller" -o "$newMode" = "repeater" ]; then
        uci set dhcp.lan.dhcpv4='server'
        uci set dhcp.lan.ra='server'
    else
        uci set dhcp.lan.dhcpv4='disabled'
        uci set dhcp.lan.ra='disabled'
    fi
    

    return 0
}



# description: change network config according to working mode
# input: $1 - new mode, "router"/"bridge"/"repeater"/"agent"/"controller"
working_mode_set_network()
{
    local newMode=$1
    local curmode=''
    local enableIfList=''
    local disableIfList=''

    `check_working_mode $newMode`
    if [ $? -ne 0 ]; then
        return -1
    fi


    uci -q del_list network.@device[0].ports=wan
    if [ "$newMode" = "bridge" -o "$newMode" = "agent" -o $newMode = "repeater" ]; then
        uci add_list network.@device[0].ports=wan
    fi

    case $newMode in
        'router' | 'controller')
            curmode='router'
            enableIfList="wan wan6"
            disableIfList="agent wwan"
            ;;
        'repeater')
            curmode='repeater'
            enableIfList="wwan"
            disableIfList="agent wan wan6"
            ;;
        'bridge' | 'agent')
            curmode='bridge'
            enableIfList="agent"
            disableIfList="wwan wan wan6"
            ;;
        *)
            ;;
    esac

    uci set network.globals.curmode=$curmode

    for interface in $enableIfList; do
        uci set network.$interface.disabled='0'
    done
    for interface in $disableIfList; do
        uci set network.$interface.disabled='1'
    done

    return 0
}



# description: change prplmesh config according to working mode
# input: $1 - new mode, "router"/"bridge"/"repeater"/"agent"/"controller"
working_mode_set_prplmesh()
{
    local newMode=$1

    `check_working_mode $newMode`
    if [ $? -ne 0 ]; then
        return -1
    fi

    case $newMode in
        'agent')
            uci batch <<EOF
                set prplmesh.config.enable='1'
                set prplmesh.config.management_mode='Multi-AP-Agent'
                set prplmesh.config.operating_mode='WDS-Repeater'
                set prplmesh.config.wired_backhaul=1
                set prplmesh.config.master=0
                set prplmesh.config.gateway=0
                set prplmesh.config.role_switched='1'
EOF
            ;;
        'controller')
            uci batch <<EOF
                set prplmesh.config.enable='1'
                set prplmesh.config.management_mode='Multi-AP-Controller-and-Agent'
                set prplmesh.config.operating_mode='Gateway'
                set prplmesh.config.wired_backhaul=0
                set prplmesh.config.master=1
                set prplmesh.config.gateway=1
                set prplmesh.config.role_switched='1'
EOF
            ;;
        *)
            uci batch <<EOF
                set prplmesh.config.enable='0'
                set prplmesh.config.management_mode='Not-Multi-AP'
                set prplmesh.config.role_switched='1'
EOF
            ;;
    esac

    return 0
}


wifi_iface_cb()
{
    local newMode=$2
    local ssid=$3
    local encryption=$4
    local key=$5
    local ifname=''
    local enableIfnameList=''
    local disableIfnameList=''
    local i=''

    config_get ifname "$1" ifname


    case $newMode in
       'repeater')
            if [ "$ifname" = 'wlan0-ap' -o "$ifname" = 'wlan1-ap' -o "$ifname" = 'wlan0-sta-rp' ]; then
                uci set wireless.$1.ssid=$ssid
                uci set wireless.$1.encryption=$encryption
                uci set wireless.$1.key=$key
            elif [ "$ifname" = 'wlan1-ap-fh' ]; then
                uci set wireless.$1.wps_pushbutton='0'
            fi
            enableIfnameList='wlan0-sta-rp'
            disableIfnameList='wlan0-ap-bh wlan0-ap-fh wlan1-ap-bh wlan1-ap-fh wlan0-sta-bh wlan1-sta-bh'
            ;;
        'bridge' | 'router')
            if [ "$ifname" = 'wlan1-ap-fh' ]; then
                uci set wireless.$1.wps_pushbutton='0'
            fi
            disableIfnameList='wlan0-ap-bh wlan0-ap-fh wlan1-ap-bh wlan1-ap-fh wlan0-sta-bh wlan1-sta-bh wlan0-sta-rp'
            ;;
        'agent')
            if [ "$ifname" = 'wlan1-ap-fh' ]; then
                uci set wireless.$1.wps_pushbutton='1'
            else
                uci set wireless.$1.wps_pushbutton='0'
            fi
            enableIfnameList='wlan0-ap-bh wlan0-ap-fh wlan1-ap-bh wlan1-ap-fh wlan0-sta-bh wlan1-sta-bh'
            disableIfnameList='wlan0-sta-rp'
            ;;
        'controller')
            if [ "$ifname" = 'wlan1-ap-fh' ]; then
                uci set wireless.$1.wps_pushbutton='1'
            else
                uci set wireless.$1.wps_pushbutton='0'
            fi
            enableIfnameList='wlan0-ap-bh wlan0-ap-fh wlan1-ap-bh wlan1-ap-fh'
            disableIfnameList='wlan0-sta-rp wlan0-sta-bh wlan1-sta-bh'
            ;;
    esac

    for i in $enableIfnameList; do
        if [ "$i" = "$ifname" ];then
            uci set wireless.$1.disabled='0'
            break
        fi
    done

    for i in $disableIfnameList; do
        if [ "$i" = "$ifname" ];then
            uci set wireless.$1.disabled='1'
            break
        fi
    done
}


# description: change wireless config according to working mode(only need for "repeater" mode)
# input: $1 - new mode, "router"/"bridge"/"repeater"/"agent"/"controller"
#        $2 - ssid of the uplink ap, repeater use only
#        $3 - encryption of the uplink ap, repeater use only
#        $4 - key of the uplink ap, repeater use only
working_mode_set_wireless()
{
    local newMode=$1
    local ssid=$2
    local encryption=$3
    local key=$4

    `check_working_mode $newMode`
    if [ $? -ne 0 ]; then
        return -1
    fi


    config_load wireless
    config_foreach wifi_iface_cb wifi-iface $newMode $ssid $encryption $key

    return 0
}



working_mode_apply()
{
    local newMode=$1

    uci commit

    # apply uci
    /etc/init.d/network restart
    /etc/init.d/dnsmasq restart
    /etc/init.d/prplmesh restart

    # notify to call hotplug
    ubus call hotplug.working-mode call '{"env":[""]}'

    return 0
}
