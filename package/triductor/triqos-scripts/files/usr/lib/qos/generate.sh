#!/bin/sh
[ -e /lib/functions.sh ] && . /lib/functions.sh || . ./functions.sh
[ -x /sbin/modprobe ] && {
	insmod="modprobe"
	rmmod="$insmod -r"
} || {
	insmod="insmod"
	rmmod="rmmod"
}

#define associative arrays: hi_hal_port_e table
hi_hal_port_e_array() {
    local key="$1"
    case "$key" in
		"eth0") echo "0";;
		"lan1") echo "1";;
		"lan2") echo "2";;
		"lan3") echo "3";;
		"lan4") echo "4";;
		"eth5") echo "5";;
		"eth6") echo "6";;
		"rgmii") echo "8";;
		"wan") echo "9";;
		"plc") echo "10";;
		"prbs") echo "11";;
		"cpu0") echo "12";;
		"cpu1") echo "13";;
		"cpu2") echo "14";;
		"cpu3") echo "15";;
		"plc0") echo "16";;
		"plc1") echo "17";;
		"plc2") echo "18";;
		"plc3") echo "19";;
		"plc4") echo "20";;
		"plc5") echo "21";;
		"plc6") echo "22";;
		"plc7") echo "23";;
		"plc8") echo "24";;
		"plc9") echo "25";;
		"plc10") echo "26";;
		"plc11") echo "27";;
		"plc12") echo "28";;
		"plc13") echo "29";;
		"plc14") echo "30";;
		"plc15") echo "31";;
		*) echo "";;
    esac
}

#define associative bitmap:hi_hal_port_u table
hi_hal_port_u_bitmap() {
	local key="$1"	
	case "$key" in
		"eth0") echo "1";;
		"lan1") echo $((1<<1));;
		"lan2") echo $((1<<2));;
		"lan3") echo $((1<<3));;
		"lan4") echo $((1<<4));;
		"eth5") echo $((1<<5));;
		"rgmii") echo $((1<<8));;
		"wan") echo $((1<<9));;
		"plc") echo $((1<<10));;
		"prbs0") echo $((1<<11));;
		"cpu0") echo $((1<<12));;
		"cpu1") echo $((1<<13));;
		"cpu2") echo $((1<<14));;
		"cpu3") echo $((1<<15));;
		*) echo "";;
	esac
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

add_insmod() {
	eval "export isset=\${insmod_$1}"
	case "$isset" in
		1) ;;
		*) {
			[ "$2" ] && append INSMOD "$rmmod $1 >&- 2>&-" "$N"
			append INSMOD "$insmod $* >&- 2>&-" "$N"; export insmod_$1=1
		};;
	esac
}

[ -e /etc/config/network ] && {
	# only try to parse network config on openwrt

	. /lib/functions/network.sh

	find_ifname() {
		local ifname
		if network_get_device ifname "$1"; then
			echo "$ifname"
		else
			echo "Device for interface $1 not found." >&2
			exit 1
		fi
	}
} || {
	find_ifname() {
		echo "Interface not found." >&2
		exit 1
	}
}

parse_matching_rule() {
	local var="$1"
	local section="$2"
	local options="$3"
	local prefix="$4"
	local suffix="$5"
	local proto="$6"
	local mport=""
	local ports=""
	local sdk_port="$7"
	local sdk_pro="$8"
	local sdk_SIP="$9"
	local sdk_DIP="${10}"

	append "$var" "$prefix" "$N"
	for option in $options; do
		case "$option" in
			proto) config_get value "$section" proto; proto="${proto:-$value}";;
		esac
	done
	if [ -n "$sdk_pro" ] && [ -n "$proto" ]; then
        append "$sdk_pro" "$proto"
	fi 
	config_get type "$section" TYPE
	case "$type" in
		classify) unset pkt; append "$var" "-m mark --mark 0/0x0f";;
		default) pkt=1; append "$var" "-m mark --mark 0/0xf0";;
		reclassify) pkt=1;;
	esac
	append "$var" "${proto:+-p $proto}"
	for option in $options; do
		config_get value "$section" "$option"
		
		case "$pkt:$option" in
			*:srchost)
				append "$var" "-s $value"
				if [ -n "$sdk_SIP" ]; then
					append "$sdk_SIP" "$value"
				fi
			;;
			*:dsthost)
				append "$var" "-d $value"	
				if [ -n "$sdk_DIP" ]; then
					append "$sdk_DIP" "$value"
				fi
			;;
			*:ports|*:srcports|*:dstports)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				lproto=${lproto:-tcp}
				case "$proto" in
					""|tcp|udp) append "$var" "-m ${proto:-tcp -p tcp} -m multiport";;
					*) unset "$var"; return 0;;
				esac
				case "$option" in
					ports)
						config_set "$section" srcports ""
						config_set "$section" dstports ""
						config_set "$section" portrange ""
						append "$var" "--ports $value"
						if [ -n "$sdk_port" ]; then
							append "$sdk_port" "$value"
						fi
					;;
					srcports)
						config_set "$section" ports ""
						config_set "$section" dstports ""
						config_set "$section" portrange ""
						append "$var" "--sports $value"
					;;
					dstports)
						config_set "$section" ports ""
						config_set "$section" srcports ""
						config_set "$section" portrange ""
						append "$var" "--dports $value"
					;;
				esac
				ports=1
			;;
			*:portrange)
				config_set "$section" ports ""
				config_set "$section" srcports ""
				config_set "$section" dstports ""
				value="$(echo "$value" | sed -e 's,-,:,g')"
				case "$proto" in
					""|tcp|udp) append "$var" "-m ${proto:-tcp -p tcp} --sport $value --dport $value";;
					*) unset "$var"; return 0;;
				esac
				ports=1
			;;
			*:connbytes)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				add_insmod xt_connbytes
				append "$var" "-m connbytes --connbytes $value --connbytes-dir both --connbytes-mode bytes"
			;;
			*:comment)
				add_insmod xt_comment
				append "$var" "-m comment --comment '$value'"
			;;
			*:tos)
				add_insmod xt_dscp
				case "$value" in
					!*) append "$var" "-m tos ! --tos $value";;
					*) append "$var" "-m tos --tos $value"
				esac
			;;
			*:dscp)
				add_insmod xt_dscp
				dscp_option="--dscp"
				[ -z "${value%%[EBCA]*}" ] && dscp_option="--dscp-class"
				case "$value" in
					!*) append "$var" "-m dscp ! $dscp_option $value";;
					*) append "$var" "-m dscp $dscp_option $value"
				esac
			;;
			*:direction)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				if [ "$value" = "out" ]; then
					append "$var" "-o $device"
				elif [ "$value" = "in" ]; then
					append "$var" "-i $device"
				fi
			;;
			*:srciface)
				append "$var" "-i $value"
			;;
			1:pktsize)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				add_insmod xt_length
				append "$var" "-m length --length $value"
			;;
			1:limit)
				add_insmod xt_limit
				append "$var" "-m limit --limit $value"
			;;
			1:tcpflags)
				case "$proto" in
					tcp) append "$var" "-m tcp --tcp-flags ALL $value";;
					*) unset $var; return 0;;
				esac
			;;
			1:mark)
				config_get class "${value##!}" classnr
				[ -z "$class" ] && continue;
				case "$value" in
					!*) append "$var" "-m mark ! --mark $class/0x0f";;
					*) append "$var" "-m mark --mark $class/0x0f";;
				esac
			;;
			1:TOS)
				add_insmod xt_DSCP
				config_get TOS "$rule" 'TOS'
				suffix="-j TOS --set-tos "${TOS:-"Normal-Service"}
			;;
			1:DSCP)
				add_insmod xt_DSCP
				config_get DSCP "$rule" 'DSCP'
				[ -z "${DSCP%%[EBCA]*}" ] && set_value="--set-dscp-class $DSCP" \
				|| set_value="--set-dscp $DSCP"
				suffix="-j DSCP $set_value"
			;;
		esac
	done
	append "$var" "$suffix"
	case "$ports:$proto" in
		1:)	parse_matching_rule "$var" "$section" "$options" "$prefix" "$suffix" "udp";;
	esac
}

config_cb() {
	option_cb() {
		return 0
	}
	case "$1" in
		interface)
			config_set "$2" "classgroup" "Default"
			config_set "$2" "upload" "128"
		;;
		classify|default|reclassify)
			option_cb() {
				append "CONFIG_${CONFIG_SECTION}_options" "$1"
			}
		;;
	esac
}

qos_parse_config() {
	config_get TYPE "$1" TYPE
	case "$TYPE" in
		interface)
			config_get_bool enabled "$1" enabled 1
			[ 1 -eq "$enabled" ] && {
				config_get classgroup "$1" classgroup
				config_set "$1" ifbdev "$C"
				C=$(($C+1))
				append INTERFACES "$1"
				config_set "$classgroup" enabled 1
				config_get device "$1" device
				[ -z "$device" ] && {
					device="$(find_ifname $1)"
					[ -z "$device" ] && exit 1
					config_set "$1" device "$device"
				}
			}
		;;
		classgroup) append CG "$1";;
		classify|default|reclassify)
			case "$TYPE" in
				classify) var="ctrules";;
				*) var="rules";;
			esac
			append "$var" "$1"
		;;
	esac
}

enum_classes() {
	local c="0"
	config_get classes "$1" classes
	config_get default "$1" default
	for class in $classes; do
		c="$(($c + 1))"
		config_set "${class}" classnr $c
		case "$class" in
			$default) class_default=$c;;
		esac
	done
	class_default="${class_default:-$c}"
}

cls_var() {
	local varname="$1"
	local class="$2"
	local name="$3"
	local type="$4"
	local default="$5"
	local tmp tmp1 tmp2
	config_get tmp1 "$class" "$name"
	config_get tmp2 "${class}_${type}" "$name"
	tmp="${tmp2:-$tmp1}"
	tmp="${tmp:-$tmp2}"
	export ${varname}="${tmp:-$default}"
}

tcrules() {
	_dir=/usr/lib/qos
	[ -e $_dir/tcrules.awk ] || _dir=.
	echo "$cstr" | awk \
		-v device="$dev" \
		-v linespeed="$rate" \
		-v direction="$dir" \
		-f $_dir/tcrules.awk
}

start_interface() {
	local iface="$1"
	local num_ifb="$2"
	config_get device "$iface" device
	config_get_bool enabled "$iface" enabled 1
	[ -z "$device" -o 1 -ne "$enabled" ] && {
		return 1 
	}
	config_get upload "$iface" upload
	config_get_bool halfduplex "$iface" halfduplex
	config_get download "$iface" download
	config_get classgroup "$iface" classgroup
	config_get_bool overhead "$iface" overhead 0
	
	download="${download:-${halfduplex:+$upload}}"
	enum_classes "$classgroup"
	for dir in ${halfduplex:-up} ${download:+down}; do
		case "$dir" in
			up)
				[ "$overhead" = 1 ] && upload=$(($upload * 98 / 100 - (15 * 128 / $upload)))
				dev="$device"
				rate="$upload"
				dl_mode=""
				prefix="cls"
			;;
			down)
				[ "$(ls -d /proc/sys/net/ipv4/conf/ifb* 2>&- | wc -l)" -ne "$num_ifb" ] && add_insmod ifb numifbs="$num_ifb"
				config_get ifbdev "$iface" ifbdev
				[ "$overhead" = 1 ] && download=$(($download * 98 / 100 - (80 * 1024 / $download)))
				dev="ifb$ifbdev"
				rate="$download"
				dl_mode=1
				prefix="d_cls"
			;;
			*) continue;;
		esac
		cstr=
		for class in $classes; do
			cls_var pktsize "$class" packetsize $dir 1500
			cls_var pktdelay "$class" packetdelay $dir 0
			cls_var maxrate "$class" limitrate $dir 100
			cls_var prio "$class" priority $dir 1
			cls_var avgrate "$class" avgrate $dir 0
			cls_var qdisc "$class" qdisc $dir ""
			cls_var filter "$class" filter $dir ""
			config_get classnr "$class" classnr
			append cstr "$classnr:$prio:$avgrate:$pktsize:$pktdelay:$maxrate:$qdisc:$filter" "$N"
		done
		append ${prefix}q "$(tcrules)" "$N"
		export dev_${dir}="ip link add ${dev} type ifb >&- 2>&-

#configure 6560 egress shaper and the default mode is bps
if [ -z "$(hi_hal_port_e_array $dev)" ]; then
	echo "ErrorPort:$dev" > /dev/null
else
	cs_cli /home/cli/api/hal/qos/egr_shaper_set -v port $(hi_hal_port_e_array $dev) rate $rate rate_mode 0 > /dev/null
fi

ip link set $dev up >&- 2>&-"
#tc qdisc del dev $dev root >&- 2>&-
#tc qdisc add dev $dev root handle 1: hfsc default ${class_default}0
#tc class add dev $dev parent 1: classid 1:1 hfsc sc rate ${rate}kbit ul rate ${rate}kbit"
	done
	[ -n "$download" ] && {
		add_insmod cls_u32
		add_insmod em_u32
		add_insmod act_connmark
		add_insmod act_mirred
		add_insmod sch_ingress
	}
if false; then
	if [ -n "$halfduplex" ]; then
		export dev_up="tc qdisc del dev $device root >&- 2>&-
tc qdisc add dev $device root handle 1: hfsc
tc filter add dev $device parent 1: prio 10 u32 match u32 0 0 flowid 1:1 action mirred egress redirect dev ifb$ifbdev"
	elif [ -n "$download" ]; then
		append dev_${dir} "tc qdisc del dev $device ingress >&- 2>&-
tc qdisc add dev $device ingress
tc filter add dev $device parent ffff: prio 1 u32 match u32 0 0 flowid 1:1 action connmark action mirred egress redirect dev ifb$ifbdev" "$N"
	fi
fi
	add_insmod cls_fw
	add_insmod sch_hfsc

	cat <<EOF
${INSMOD:+$INSMOD$N}${dev_up:+$dev_up
$clsq
}${ifbdev:+$dev_down
$d_clsq
$d_clsl
$d_clsf
}
EOF
	unset INSMOD clsq clsf clsl d_clsq d_clsl d_clsf dev_up dev_down
}

start_interfaces() {
	local C="$1"
	for iface in $INTERFACES; do
		start_interface "$iface" "$C"
	done
}

add_rules() {
	local var="$1"
	local rules="$2"
	local prefix="$3"
	
	for rule in $rules; do
		unset iptrule
		config_get target "$rule" target
		config_get target "$target" classnr
		config_get options "$rule" options

		## If we want to override the TOS field, let's clear the DSCP field first.
		[ ! -z "$(echo $options | grep 'TOS')" ] && {
			s_options=${options%%TOS}
			add_insmod xt_DSCP
			parse_matching_rule iptrule "$rule" "$s_options" "$prefix" "-j DSCP --set-dscp 0"
			append "$var" "$iptrule" "$N"
			unset iptrule
		}

		target=$(($target | ($target << 4)))
		parse_matching_rule iptrule "$rule" "$options" "$prefix" "-j MARK --set-mark $target/0xff"
		append "$var" "$iptrule" "$N"
	done
}

sdk_ifc_set() {
	local sdk_pri="$1"
	local sdk_sip="$2"
	local sdk_dip="$3"
	local sdk_pro="$4"
	local sdk_port="$5"
	local egr=""
	local ifc_prefix="cs_cli /home/cli/api/hal/flow/ifc_set -v label 1 entry_pri 0\
 fwd_act_en 1 fwd_act 7"

	if [ ! -d "/var/run/qos" ]; then
		 mkdir /var/run/qos
	fi

	if [ "${#sdk_sip}" -ge "16" ] || [ "${#sdk_dip}" -ge "16" ]; then
		return
	fi
	config_get device "$iface" device
	egr=$(hi_hal_port_u_bitmap $device)

	if [[ -n "$sdk_port" ]]; then
		for port in $(echo $sdk_port | tr ',' ' '); do
			append ifc_command "$ifc_prefix"
			append ifc_command " egress $egr"
			if [[ -n "$sdk_pri" ]]; then
				append ifc_command  " pq_mode 3 pq $((4-$sdk_pri))"
			fi
			if [[ -n "$sdk_sip" ]]; then
				append ifc_command " sip_en 1 sip $sdk_sip sipmask 255.255.255.255"
			fi
			if [[ -n "$sdk_dip" ]]; then
				append ifc_command " dip_en 1 dip $sdk_dip dipmask 255.255.255.255"
			fi
			if [[ -n "$sdk_pro" ]]; then
				if [[ -n "$(ipprotos_map $sdk_pro)" ]]; then
					append ifc_command " proto_en 1 proto $(ipprotos_map $sdk_pro)"
				else
					return
				fi
			fi
			if [[ -n "$port" ]]; then
				${ifc_command}  sport_en 1 sport $port > /dev/null
				echo "${ifc_command}  sport_en 1 sport $port" >> /var/run/qos/ifc_rules
				${ifc_command} dport_en 1 dport $port > /dev/null 
				echo "${ifc_command}  dport_en 1 dport $port" >> /var/run/qos/ifc_rules
			else
				return
			fi

			unset ifc_command
	
		done
	else
			append ifc_command "$ifc_prefix"
			append ifc_command " egress $egr"
			if [[ -n "$sdk_pri" ]]; then
				append ifc_command  " pq_mode 3 pq $((4-$sdk_pri))"
			fi
			if [[ -n "$sdk_sip" ]]; then
				append ifc_command " sip_en 1 sip $sdk_sip sipmask 255.255.255.255"
			fi
			if [[ -n "$sdk_dip" ]]; then
				append ifc_command " dip_en 1 dip $sdk_dip dipmask 255.255.255.255"
			fi
			if [[ -n "$sdk_pro" ]]; then
				if [[ -n "$(ipprotos_map $sdk_pro)" ]]; then
					append ifc_command " proto_en 1 proto $(ipprotos_map $sdk_pro)"
				else
					return
				fi
			fi
			
			${ifc_command} > /dev/null
			echo "$ifc_command" >> /var/run/qos/ifc_rules
			unset ifc_command
	fi
}

sdk_add_rules() {
    local var="$1"
    local rules="$2"
    local prefix="$3"

    for rule in $rules; do
        unset iptrule
        config_get target "$rule" target
        config_get target "$target" classnr
        config_get options "$rule" options

        parse_matching_rule iptrule "$rule" "$options" "$prefix" "-j MARK --set-mark $target/0xff" "" sdk_ports sdk_proto sdk_sip sdk_dip
		sdk_ifc_set "$target" "$sdk_sip" "$sdk_dip" "$sdk_proto" "$sdk_ports" 
		unset sdk_ports
		unset sdk_proto
		unset sdk_sip
		unset sdk_dip
    done
}


start_cg() {
	local cg="$1"
	local iptrules
	local pktrules
	local sizerules
	enum_classes "$cg"
	for command in $iptables; do
		add_rules iptrules "$ctrules" "$command -w -t mangle -A qos_${cg}_ct"
	done
	config_get classes "$cg" classes
	for class in $classes; do
		config_get mark "$class" classnr
		config_get maxsize "$class" maxsize
		[ -z "$maxsize" -o -z "$mark" ] || {
			add_insmod xt_length
			for command in $iptables; do
				append pktrules "$command -w -t mangle -A qos_${cg} -m mark --mark $mark/0x0f -m length --length $maxsize: -j MARK --set-mark 0/0xff" "$N"
			done
		}
	done
	for command in $iptables; do
		add_rules pktrules "$rules" "$command -w -t mangle -A qos_${cg}"
	done
	for iface in $INTERFACES; do
		config_get classgroup "$iface" classgroup
		config_get device "$iface" device
		config_get ifbdev "$iface" ifbdev
		config_get upload "$iface" upload
		config_get download "$iface" download
		config_get halfduplex "$iface" halfduplex
		download="${download:-${halfduplex:+$upload}}"
		for command in $iptables; do
			append up "$command -w -t mangle -A OUTPUT -o $device -j qos_${cg}" "$N"
			append up "$command -w -t mangle -A FORWARD -o $device -j qos_${cg}" "$N"
		done
	done
	cat <<EOF
$INSMOD
EOF

for command in $iptables; do
	cat <<EOF
	$command -w -t mangle -N qos_${cg} 
	$command -w -t mangle -N qos_${cg}_ct
EOF
done
cat <<EOF
	${iptrules:+${iptrules}${N}}
EOF
for command in $iptables; do
	cat <<EOF
	$command -w -t mangle -A qos_${cg}_ct -j CONNMARK --save-mark --mask 0xff
	$command -w -t mangle -A qos_${cg} -j CONNMARK --restore-mark --mask 0x0f
	$command -w -t mangle -A qos_${cg} -m mark --mark 0/0x0f -j qos_${cg}_ct
EOF
done
cat <<EOF
$pktrules
EOF
for command in $iptables; do
	cat <<EOF
	$command -w -t mangle -A qos_${cg} -j CONNMARK --save-mark --mask 0xff
EOF
done
cat <<EOF
$up$N${down:+${down}$N}
EOF
	unset INSMOD
}

start_firewall() {
	add_insmod xt_multiport
	add_insmod xt_connmark
	stop_firewall
	for group in $CG; do
		start_cg $group
	done
}

stop_firewall() {
	# Builds up a list of iptables commands to flush the qos_* chains,
	# remove rules referring to them, then delete them

	# Print rules in the mangle table, like iptables-save
	for command in $iptables; do
		$command -w -t mangle -S |
			# Find rules for the qos_* chains
			grep -E '(^-N qos_|-j qos_)' |
			# Exclude rules in qos_* chains (inter-qos_* refs)
			grep -v '^-A qos_' |
			# Replace -N with -X and hold, with -F and print
			# Replace -A with -D
			# Print held lines at the end (note leading newline)
			sed -e '/^-N/{s/^-N/-X/;H;s/^-X/-F/}' \
				-e 's/^-A/-D/' \
				-e '${p;g}' |
			# Make into proper iptables calls
			# Note: awkward in previous call due to hold space usage
			sed -n -e "s/^./${command} -w -t mangle &/p"
	done
}

sdk_start_qos() {

	config_get device "$iface" device
	if [ -z "$device" ]; then
		return 1
	fi

	if [ ! -d "/var/run/qos" ]; then
		 mkdir /var/run/qos
	fi
	#set up sch mode
	cs_cli /home/cli/api/hal/qos/up_sch_mode_set -v wan_ifname $device mode 2 q0_weight 1\
	q1_weight 1 q2_weight 1 q3_weight 1 q4_weight 1 q5_weight 1 q6_weight 1 q7_weight 1  >> /dev/null
	
	echo "cs_cli /home/cli/api/hal/qos/up_sch_mode_set -v wan_ifname $device mode 2 q0_weight 1\
	q1_weight 1 q2_weight 1 q3_weight 1 q4_weight 1 q5_weight 1 q6_weight 1 q7_weight 1"  >> /var/run/qos/other_config
	
	for command in $iptables; do
		sdk_add_rules iptrules "$ctrules" "$command -w -t mangle -A qos_${cg}_ct"
	done
}

sdk_stop_qos() {
	filename="/var/run/qos/other_config"
  	search_str="wan_ifname"
	local device=""

  	while read line; do
  	device=$(echo "$line" | sed -n "s/.*$search_str \([^ ]*\) .*/\1/p")
  	if [ -n "$device" ]; then
	      cs_cli /home/cli/api/hal/qos/egr_shaper_set -v port $(hi_hal_port_e_array $device) rate 0 rate_mode 0 > /dev/null
	      cs_cli /home/cli/api/hal/qos/up_sch_mode_set -v wan_ifname $device mode 0 q0_weight 7\
	      q1_weight 7 q2_weight 7 q3_weight 7 q4_weight 7 q5_weight 7 q6_weight 7 q7_weight 7  > /dev/null
		
        fi
        done <"$filename"
	echo -n "" >/var/run/qos/other_config


	sed -i 's|ifc_set|ifc_del|g' /var/run/qos/ifc_rules
	#Associate file descriptor 3 with ifc_rules file
	exec 3< /var/run/qos/ifc_rules
	#Use file descriptor 3 to read the file
    while read -u 3 line        
    do                          
		${line} > /dev/null 
    done
	#Close the file associated with file descriptor 3
    exec 3<&-     

	echo -n "" > /var/run/qos/ifc_rules	
}

C="0"
INTERFACES=""
[ -e ./qos.conf ] && {
	. ./qos.conf
	config_cb
} || {
	config_load qos
	config_foreach qos_parse_config
}

C="0"
for iface in $INTERFACES; do
	export C="$(($C + 1))"
done

[ -x /usr/sbin/ip6tables ] && {
	iptables="ip6tables iptables"
} || {
	iptables="iptables"
}

case "$1" in
	all)
		start_interfaces "$C"
		#start_firewall
		sdk_start_qos
	;;
	interface)
		start_interface "$2" "$C"
	;;
	interfaces)
		start_interfaces
	;;
	firewall)
		case "$2" in
			stop)
				#stop_firewall
				sdk_stop_qos
			;;
			start|"")
				#start_firewall
				sdk_start_qos
			;;
		esac
	;;
esac
