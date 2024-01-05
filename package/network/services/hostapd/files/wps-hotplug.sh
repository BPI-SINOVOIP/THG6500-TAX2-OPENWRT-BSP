#!/bin/sh

wps_catch_credentials() {
	local iface ifaces ifc ifname ssid encryption key radio radios
	local found=0

	. /usr/share/libubox/jshn.sh
	ubus -S -t 30 listen wps_credentials | while read creds; do
		json_init
		json_load "$creds"
		json_select wps_credentials || continue
		json_get_vars ifname ssid key encryption
		local ifcname="$ifname"
		json_init
		json_load "$(ubus -S call network.wireless status)"
		json_get_keys radios
		for radio in $radios; do
			json_select $radio
			json_select interfaces
			json_get_keys ifaces
			for ifc in $ifaces; do
				json_select $ifc
				json_get_vars ifname
				[ "$ifname" = "$ifcname" ] && {
					ubus -S call uci set "{\"config\":\"wireless\", \"type\":\"wifi-iface\",		\
								\"match\": { \"device\": \"$radio\", \"encryption\": \"wps\" },	\
								\"values\": { \"encryption\": \"$encryption\", 			\
										\"ssid\": \"$ssid\", 				\
										\"key\": \"$key\" } }"
					ubus -S call uci commit '{"config": "wireless"}'
					ubus -S call uci apply
				}
				json_select ..
			done
			json_select ..
			json_select ..
		done
	done
}

if [ "$ACTION" = "released" ] && [ "$BUTTON" = "wps" ]; then
	# If the button was pressed for 3 seconds or more, trigger WPS on
	# wpa_supplicant only, no matter if hostapd is running or not.  If
	# was pressed for less than 3 seconds, try triggering on
	# hostapd. If there is no hostapd instance to trigger it on or WPS
	# is not enabled on them, trigger it on wpa_supplicant.
	management_mode=`uci -q get prplmesh.config.management_mode`
	if [ -n "$management_mode" -a "$management_mode" = "Multi-AP-Controller-and-Agent" ]; then
		if [ "$SEEN" -lt 3 ] ; then
                	wps_done=0
                	ubusobjs="$( ubus -S list hostapd.* )"
                	for ubusobj in $ubusobjs; do
				ifname="$(echo $ubusobj | cut -d'.' -f2 )"
                        	ubus -S call $ubusobj wps_start && wps_done=1
				iwpriv ${ifname} ssidhide 0
                	done
                	[ $wps_done = 0 ] || return 0
		else
			/bin/scripts/modeSet.sh router
		fi
	elif [ -n "$management_mode" -a "$management_mode" = "Multi-AP-Agent" ]; then
		if [ "$SEEN" -lt 3 ] ; then
			ignore_sta_wps=0
			mesh_state=`uci -q get prplmesh.config.onboarded`
			if [ "$mesh_state" = "1" ] ; then
				ignore_sta_wps=1		
			fi
			logger -t wps_button -p notice "mesh_state=$mesh_state" "ignore_sta_wps=$ignore_sta_wps"
			ubusobjs="$( ubus -S list wpa_supplicant.* )"
        		for ubusobj in $ubusobjs; do
                		ifname="$(echo $ubusobj | cut -d'.' -f2 )"
                		multi_ap=""
                		if [ -e "/var/run/wpa_supplicant-${ifname}.conf.is_multiap" -a "$ignore_sta_wps" = "0" ]; then
                        		wpa_cli -i ${ifname} WPS_PBC multi_ap=1
					logger -t wps_button -p notice "ubusobjs=$ubusobjs" "start wp"
                		fi
        		done
			wps_done=0
                        ubusobjs="$( ubus -S list hostapd.* )"
                        for ubusobj in $ubusobjs; do
				if [ "$ignore_sta_wps" = "1" ]; then
					ifname="$(echo $ubusobj | cut -d'.' -f2 )"
                                	ubus -S call $ubusobj wps_start && wps_done=1
					logger -t wps_button -p notice "ubusobjs=$ubusobjs" "start wp"
					iwpriv ${ifname} ssidhide 0
				fi
                        done
                        [ $wps_done = 0 ] || return 0
		else
			/bin/scripts/modeSet.sh router
		fi
	else
	if [ "$SEEN" -lt 3 ] ; then
		wps_done=0
		ubusobjs="$( ubus -S list hostapd.* )"
		for ubusobj in $ubusobjs; do
			ubus -S call $ubusobj wps_start && wps_done=1
		done
		[ $wps_done = 0 ] || return 0
	fi
	wps_done=0
	ubusobjs="$( ubus -S list wpa_supplicant.* )"
	for ubusobj in $ubusobjs; do
		ifname="$(echo $ubusobj | cut -d'.' -f2 )"
		multi_ap=""
		if [ -e "/var/run/wpa_supplicant-${ifname}.conf.is_multiap" ]; then
			ubus -S call $ubusobj wps_start '{ "multi_ap": true }' && wps_done=1
		else
			ubus -S call $ubusobj wps_start && wps_done=1
		fi
	done
	[ $wps_done = 0 ] || wps_catch_credentials &
	fi
fi

return 0
