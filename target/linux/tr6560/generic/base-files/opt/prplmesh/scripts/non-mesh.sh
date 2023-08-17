#!/bin/sh
. /lib/functions/system.sh
. /lib/functions.sh

reload_wireless_config()
{
	rm -f /etc/config/wireless
	wifi config
	
uci batch << 'EOF'
set wireless.default_radio0=wifi-iface
set wireless.default_radio0.device='radio0'
set wireless.default_radio0.network='lan'
set wireless.default_radio0.mode='ap'
set wireless.default_radio0.ssid='OpenWrt_2g'
set wireless.default_radio0.encryption='none'
set wireless.default_radio0.cwmp_WLANConfiguration_instance='1'
set wireless.default_radio0.ifname='wlan0'

set wireless.default_radio1=wifi-iface
set wireless.default_radio1.device='radio1'
set wireless.default_radio1.network='lan'
set wireless.default_radio1.mode='ap'
set wireless.default_radio1.ssid='OpenWrt_5g'
set wireless.default_radio1.encryption='none'
set wireless.default_radio1.cwmp_WLANConfiguration_instance='2'
set wireless.default_radio1.ifname='wlan1'
EOF
	config_load wireless
}

set_normal_gw()
{
	reload_wireless_config
	uci set prplmesh.config.management_mode='Not-Multi-AP'
	uci set prplmesh.config.operating_mode='Gateway'
	uci set prplmesh.config.enable='1'
	uci set prplmesh.radio0.hostap_iface='wlan0'
	uci set prplmesh.radio1.hostap_iface='wlan1'

	uci set network.wan.disabled=0
	uci set network.wan6.disabled=0
	uci del_list network.@device[0].ports=wan
	uci set network.lan.proto='static'
	uci commit
	/etc/init.d/network restart
	/etc/init.d/prplmesh restart
}
