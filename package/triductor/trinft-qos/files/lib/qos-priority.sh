#!/bin/sh
# based on static.sh
# Copyright © 2023 Triductor Technology(Suzhou) Inc. - http://www.triductor.com/
#

. /lib/nft-qos/core.sh

qosdef_validate_qosprio() {
	uci_load_validate nft-qos default "$1" "$2" \
		'qosEnable:bool:0'
}

#define Protocol convert to protocol number function
ipprotos_map() {
    local key="$1"
    case "$key" in
        "tcp") echo "6";;
        "udp") echo "17";;
        "icmp") echo "1";;
        "icmpv6") echo "58";;
        "igmp") echo "2";;
        *) echo "";;
    esac
}

# append rule for mac qos
qosdef_append_rule_prio() { # <section>
	local sourceMac destinationMac sourceIp destinationIp
	local sourcePort destinationPort protocol
	local qosPriority dscpEnable dscpPriority vlan8021pEnable vlan8021p 
	local ipdaddr


	config_get destinationMac $1 destinationMac
	config_get sourceMac $1 sourceMac
	config_get sourceIp $1 sourceIp
	config_get destinationIp $1 destinationIp
	config_get sourcePort $1 sourcePort
	config_get destinationPort $1 destinationPort
	config_get protocol $1 protocol  

	config_get qosPriority $1 qosPriority  
	config_get dscpEnable $1 dscpEnable
	config_get dscpPriority $1 dscpPriority

	#Uppercase characters are converted to lowercase characters
	protocol=$(echo "$protocol" | awk '{print tolower($0)}')
	[ -n "$destinationMac" ] && {
		destinationMac=$(echo "$destinationMac" | awk '{print tolower($0)}')
	}

	if [ "$qosPriority" -gt 7 ] || [ "$qosPriority" -lt 0 ]; then
		return 1
	fi

	[ "$dscpEnable" -eq 1 ] && {
		if [ "$dscpPriority" -gt 63 ] || [ "$dscpPriority" -lt 0 ]; then
			return 1
		fi
	}

	[ "$dscpEnable" -eq 0 ] && {
		dscpPriority=""
	}
	[ -n "$destinationMac" ] && {
		local neigh_output
		neigh_output=$(ip -4 neigh show dev br-lan)
		ipdaddr=$(echo "$neigh_output" | grep "$destinationMac" | awk '{print $1}' | tr '\n' ',' | sed 's/,$//')
	}
	[ -n "$ipdaddr" ] && {
		destinationMac=""
		destinationIp="$ipdaddr"
	}
	if [ -n "$protocol" ]; then
		protocol=$(echo "$protocol" | tr ',' '\n')
		for proto in $protocol; do
			qosdef_append_rule_qos_priority "$sourceMac" "$destinationMac" "$sourceIp" "$destinationIp" "$sourcePort" "$destinationPort" "$proto" "$(($qosPriority+1))" "$dscpPriority"
		done
	else
			qosdef_append_rule_qos_priority "$sourceMac" "$destinationMac" "$sourceIp" "$destinationIp" "$sourcePort" "$destinationPort" "" "$(($qosPriority+1))" "$dscpPriority"
	fi
}

qosdef_flush_qosprio() {
	local wan_ext		
	#clear download
	#Clear the br-lan port TC configuration
	eval "tc qdisc del dev br-lan root 2>/dev/null"
	#clear the qos_priority_ct configuration
	qosdef_flush_table "$NFT_QOS_INET_FAMILY" qos_priority_ct
	
	#clear upload
	wan_ext=$(ifconfig -a | grep -o "wan\.[0-9]\+")
	[ -n "$wan_ext" ] && {
		cs_cli /home/cli/api/protocol/cfe/intf/setpri -v ifname $wan_ext pri 0  >/dev/null
	}
	
	if [ -d "/var/run/qos" ] && [ -e  "/var/run/qos/ifc_qos_priority" ]; then
		sed -i 's|ifc_set|ifc_del|g' /var/run/qos/ifc_qos_priority
		#Associate file descriptor 3 with ifc_qos_priority file
		exec 3< /var/run/qos/ifc_qos_priority
		#Use file descriptor 3 to read the file
		while read -u 3 line
		do
			${line} > /dev/null
		done
		#Close the file associated with file descriptor 3
		exec 3<&-

		echo -n "" > /var/run/qos/ifc_qos_priority
	fi
}

# Configure the br-lan port TC
qosdef_config_tc(){ #<dev>
	local dev="$1"
	#configure root 
	eval "tc qdisc add dev "$dev" root handle 1: prio bands 8 priomap 0 1 2 3 4 5 6 7  2>/dev/null"
	#configure qdisc
	eval "tc qdisc add dev "$dev" parent 1:1 handle 10: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:2 handle 20: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:3 handle 30: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:4 handle 40: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:5 handle 50: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:6 handle 60: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:7 handle 70: pfifo 2>/dev/null"
	eval "tc qdisc add dev "$dev" parent 1:8 handle 80: pfifo 2>/dev/null"
	#configure filter
	eval "tc filter add dev "$dev" parent 1: prio 1 handle 0x11110011 fw flowid 1:1  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 2 handle 0x11110022 fw flowid 1:2  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 3 handle 0x11110033 fw flowid 1:3  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 4 handle 0x11110044 fw flowid 1:4  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 5 handle 0x11110055 fw flowid 1:5  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 6 handle 0x11110066 fw flowid 1:6  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 7 handle 0x11110077 fw flowid 1:7  2>/dev/null"
	eval "tc filter add dev "$dev" parent 1: prio 8 handle 0x11110088 fw flowid 1:8  2>/dev/null"
}

qosdef_config_qos_up() {
	local sourceMac destinationMac sourceIp destinationIp
	local sourcePort destinationPort protocol
	local qosPriority dscpEnable dscpPriority vlan8021pEnable vlan8021p 
	local ifc_command proto_is_correct
	local ifc_prefix="cs_cli /home/cli/api/hal/flow/ifc_set -v label 1 entry_pri 0 \
fwd_act_en 1 fwd_act 7"

	config_get destinationMac $1 destinationMac
	config_get sourceMac $1 sourceMac
	config_get sourceIp $1 sourceIp
	config_get destinationIp $1 destinationIp
	config_get sourcePort $1 sourcePort
	config_get destinationPort $1 destinationPort
	config_get protocol $1 protocol  

	config_get qosPriority $1 qosPriority  
	config_get dscpEnable $1 dscpEnable
	config_get dscpPriority $1 dscpPriority
	config_get vlan8021pEnable $1 vlan8021pEnable
	config_get vlan8021p $1 vlan8021p

	if [ ! -d "/var/run/qos" ]; then
         mkdir /var/run/qos
	fi
	
	#Uppercase characters are converted to lowercase characters
	protocol=$(echo "$protocol" | awk '{print tolower($0)}')

	if [ "$qosPriority" -gt 7 ] || [ "$qosPriority" -lt 0 ]; then
		return 1
	fi

	[ "$dscpEnable" -eq 1 ] && {
		if [ "$dscpPriority" -gt 63 ] || [ "$dscpPriority" -lt 0 ]; then
			return 1
		fi
	}
	wan_ext=$(ifconfig -a | grep -o "wan\.[0-9]\+")
	[ "$vlan8021pEnable" -eq 1 ] && [ -z "$wan_ext" ] && return 1
	[ "$vlan8021pEnable" -eq 1 ] && [ -n "$vlan8021p" ] && {
		if [ "$vlan8021p" -gt 7 ] || [ "$vlan8021p" -lt 0 ]; then
			return 1
		fi
		cs_cli /home/cli/api/protocol/cfe/intf/setpri -v ifname $wan_ext pri $vlan8021p  >/dev/null
	}
	cs_cli /home/cli/api/hal/qos/up_sch_mode_set  -v wan_ifname wan mode 0  >/dev/null
	
	if [ -n "$protocol" ]; then
		protocol=$(echo "$protocol" | tr ',' '\n')
		for proto in $protocol; do
			ifc_command="$ifc_prefix"
			proto_is_correct=$(ipprotos_map "$proto")
			[ -n "$proto_is_correct" ] && {	
				ifc_command="$ifc_command proto_en 1 proto $(ipprotos_map "$proto")"
				if [ -n "$destinationMac" ]; then
					ifc_command="$ifc_command smac_en 1 smac $sourceMac dmac_en 1 dmac $destinationMac"
				elif [ -n "$sourceIp" ]; then
					ifc_command="$ifc_command sip_en 1 sip $sourceIp dip_en 1 dip $destinationIp"
				fi

				if [ "$proto" == "tcp" ] || [ "$proto" == "udp" ]; then
					[ -n "$sourcePort" ] && {
						ifc_command="$ifc_command sport_en 1 sport $sourcePort"
					}
					[ -n "$destinationPort" ] && {
						ifc_command="$ifc_command dport_en 1 dport $destinationPort"
					}
				fi

				[ -n "$qosPriority" ] && {
					ifc_command="$ifc_command pq_mode 3 pq $qosPriority"
				}
				[ "$dscpEnable"  -eq 1 ] && {
					ifc_command="$ifc_command act_dscp_en 1 act_dscp $dscpPriority"
				}
			
				$ifc_command >/dev/null
				echo "$ifc_command"  >> /var/run/qos/ifc_qos_priority
				unset ifc_command
			}
		done
	elif [ -z "$protocol" ]; then
		ifc_command="$ifc_prefix"
		if [ -n "$destinationMac" ]; then
			ifc_command="$ifc_command smac_en 1 smac $sourceMac dmac_en 1 dmac $destinationMac"
		elif [ -n "$sourceIp" ]; then
			ifc_command="$ifc_command sip_en 1 sip $sourceIp dip_en 1 dip $destinationIp"
		fi

		[ -n "$sourcePort" ] && {
			ifc_command="$ifc_command sport_en 1 sport $sourcePort"
		}
		[ -n "$destinationPort" ] && {
			ifc_command="$ifc_command dport_en 1 dport $destinationPort"
		}
		[ -n "$qosPriority" ] && {
			ifc_command="$ifc_command pq_mode 3 pq $qosPriority"
		}
		[ "$dscpEnable"  -eq 1 ] && {
			ifc_command="$ifc_command act_dscp_en 1 act_dscp $dscpPriority"
		}

		$ifc_command >/dev/null
		echo "$ifc_command"  >> /var/run/qos/ifc_qos_priority
		unset ifc_command	
	fi
}

qosdef_config_qos_down() {
	local config="$1"
	
	qosdef_append_rule_prio $config

}

qosdef_parse_matching_rule() {
	local destinationMac sourceMac sourceIp destinationIp
	local is_upload is_download
	
	config_get destinationMac $1 destinationMac
	config_get sourceMac $1 sourceMac
	config_get sourceIp $1 sourceIp
	config_get destinationIp $1 destinationIp

	[ -z "$destinationMac" ] && [ -z "$sourceMac" ] && [ -z "$sourceIp" ] && [ -z "$destinationIp" ] && return 1
	br_lan_mac=$(ip link show dev br-lan |awk '/link/{print $2}')
	br_lan_mac=$(echo "$br_lan_mac" | awk '{print tolower($0)}')
	destinationMac=$(echo "$destinationMac" | awk '{print tolower($0)}')
	
	if [ -n "$destinationMac" ]; then
		[ -z "$sourceMac" ] && return 1
		[[ -n "$sourceIp" || -n "$destinationIp" ]] && return 1
		is_download=$(ip -4 neigh show dev br-lan | grep "$destinationMac")
		if [ "$destinationMac" == "$br_lan_mac" ]; then
			qosdef_config_qos_up "$1" 
		elif [ -n "$is_download" ]; then
			qosdef_config_qos_down "$1"
		fi
	elif [ -n "$sourceIp" ]; then
		[ -z "$destinationIp" ] && return 1
		[[ -n "$sourceMac" || -n "$destinationMac" ]] && return 1
		is_upload=$(ip -4 neigh show dev br-lan | grep  "$sourceIp")
		is_download=$(ip -4 neigh show dev br-lan| grep  "$destinationIp")
		if [ -n "$is_upload" ]; then
			qosdef_config_qos_up "$1"
		elif [ -n "$is_download" ]; then		
			qosdef_config_qos_down "$1"
		fi

	fi	
}

#init traffic priority
qosdef_init_qosprio() {
	local qos_section="priority"
	local hook_dl="postrouting"
	local table_name=$NFT_QOS_INET_FAMILY
	local chain_name="download"

	[ "$2" = 0 ] || {
		logger -t nft-qos-priority "validation failed"
		return 1
	}

	[ "$qosEnable" -eq 0 ] && return
	
	qosdef_config_tc "br-lan"
	qosdef_appendx "table $table_name qos_priority_ct {\n"
	qosdef_appendx "\tchain $chain_name {\n"
	qosdef_append_chain_def filter $hook_dl 0 accept

	config_foreach qosdef_parse_matching_rule "$qos_section"

	qosdef_appendx "\t}\n}\n"
}
