#!/bin/sh
#
# Copyright © 2023 Triductor Technology(Suzhou) Inc. - http://www.triductor.com/
#

. /lib/nft-qos/core.sh

qosdef_validate_static() {
	uci_load_validate nft-qos default "$1" "$2" \
		'limit_enable:bool:0' \
		'limit_type:maxlength(8)' \
		'static_unit_dl:string:kbytes' \
		'static_unit_ul:string:kbytes' \
		'static_rate_dl:uinteger:0' \
		'static_rate_ul:uinteger:0'
}

# append rule for static qos
qosdef_append_rule_sta() { # <section> <operator> <default-unit> <default-rate> <ip_oper>
	local unit rate urunit drunit urate drate
	local operator=$2 ip_oper=$5
	local ipv4_addr ipv6_addr lookup_result

	config_get macaddr $1 macaddr
	[ -z "$macaddr" ] && return

	if [ "$operator" == "saddr" ]; then
		config_get urunit $1 urunit $3
		config_get urate $1 urate $4
		rate="$urate"
		unit="$urunit"
	elif [ "$operator" == "daddr" ]; then
		config_get drunit $1 drunit $3
		config_get drate $1 drate $4
		rate="$drate"
		unit="$drunit"
	else
		return
	fi
	[ "$rate" -eq 0 ] && return

	config_get url $1 url
	if [ -n "$url" ]; then
		for domain in $url; do
			lookup_result=$(nslookup "$domain")
			ipv4_addr=$(echo "$lookup_result" | awk '/^Address: [0-9.]+$/ { printf "%s ",$2 }')
			ipv6_addr=$(echo "$lookup_result" | awk '/^Address: / && /:[0-9a-fA-F:.]+$/ { printf "%s ",$2 }')
			ipv4_addr=$(echo "$ipv4_addr" | tr ' ' ',' | sed 's/,$//')
			ipv6_addr=$(echo "$ipv6_addr" | tr ' ' ',' | sed 's/,$//')

			if [ -n "$ipv4_addr" ]; then
				qosdef_append_rule_ip_limit  $operator $unit $rate $macaddr "ip" $ip_oper "{$ipv4_addr}"
			fi

			if [ -n "$ipv6_addr" ]; then                                                                  
           		qosdef_append_rule_ip_limit  $operator $unit $rate $macaddr "ip6" $ip_oper "{$ipv6_addr}"
            fi        
		done
	else
		qosdef_append_rule_ip_limit  $operator $unit $rate $macaddr		
	fi
}

# append chain for static qos
qosdef_append_chain_sta() { # <hook> <name> <section> <unit> <rate>
	local hook=$1 name=$2
	local config=$3 operator ip_oper

	case "$name" in
		download) operator="daddr" ip_oper="saddr";;
		upload) operator="saddr" ip_oper="daddr"
	esac

	qosdef_appendx "\tchain $name {\n"
	qosdef_append_chain_def filter $hook 0 accept
#	qosdef_append_rule_limit_whitelist $name
	config_foreach qosdef_append_rule_sta $config $operator $4 $5 $ip_oper
	qosdef_appendx "\t}\n"
}

qosdef_flush_static() {
	qosdef_flush_table "$NFT_QOS_BRIDGE" rate-limit-mac
}

# static limit rate init
qosdef_init_static() {
	local hook_ul="prerouting" hook_dl="postrouting"

	[ "$2" = 0 ] || {
		logger -t rate-limit-mac "validation failed"
		return 1
	}

	[ $limit_enable -eq 0 ] && return 1

#	[ -z "$NFT_QOS_HAS_BRIDGE" ] && {
#		hook_ul="postrouting"
#		hook_dl="prerouting"
#	}

	qosdef_appendx "table $NFT_QOS_BRIDGE rate-limit-mac {\n"
	qosdef_append_chain_sta $hook_ul upload client $static_unit_ul $static_rate_ul
	qosdef_append_chain_sta $hook_dl download client $static_unit_dl $static_rate_dl
	qosdef_appendx "}\n"
}
