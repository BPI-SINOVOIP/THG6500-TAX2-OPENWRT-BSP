#!/bin/sh
#
# Copyright © 2023 Triductor Technology(Suzhou) Inc. - http://www.triductor.com/
#

# for uci_validate_section()
. /lib/functions/procd.sh

NFT_QOS_HAS_BRIDGE=
NFT_QOS_INET_FAMILY=ip
NFT_QOS_BRIDGE=bridge
NFT_QOS_SCRIPT_TEXT=
NFT_QOS_SCRIPT_FILE=/tmp/qos.nft

qosdef_appendx() { # <string to be appended>
	NFT_QOS_SCRIPT_TEXT="$NFT_QOS_SCRIPT_TEXT""$1"
}

qosdef_append_chain_def() { # <type> <hook> <priority> <policy>
	qosdef_appendx "\t\ttype $1 hook $2 priority $3; policy $4;\n"
}

qosdef_append_chain_ingress() { # <type> <device> <priority> <policy>
	qosdef_appendx "\t\ttype $1 hook ingress device $2 priority $3; policy $4;\n"
}

# qosdef_append_rule_{MATCH}_{STATEMENT}
qosdef_append_rule_ip_limit() { #  <operator> <unit> <rate> <macaddr> <ip_ver> <ip_oper> <ipaddr>
	local operator=$1
	local unit=$2
	local rate=$3
	local macaddr=$4
	local ip_ver=$5
	local ip_oper=$6
	local ipaddr=$7

	[ -z "$macaddr" ] && return
	if [ -n "$ip_ver" ]; then
		[ -z "$ip_oper" -o -z "$ipaddr" ] && return
	fi

	if [ "$ip_ver" == "ip" ]; then
			qosdef_appendx \
				"\t\t ether $operator $macaddr $ip_ver $ip_oper $ipaddr meta mark set 0x11110000 limit rate over $rate $unit/second drop\n"

	elif [ "$ip_ver" == "ip6" ]; then
			qosdef_appendx \
				"\t\t ether $operator $macaddr $ip_ver $ip_oper $ipaddr meta mark set 0x11110000 limit rate over $rate $unit/second drop\n"
	else
			qosdef_appendx \
				"\t\t ether $operator $macaddr meta mark set 0x11110000 limit rate over $rate $unit/second drop\n"
	fi	
}

# qosdef_append_rule_{MATCH}_{STATEMENT}
qosdef_append_rule_qos_priority() { # <smacaddr> <dmacaddr> <sipaddr> <dipaddr> <sport> <dport> <protocol> <qospriority> <dscppriority>
	local smacaddr=$1
	local dmacaddr=$2
	local sipaddr=$3
	local dipaddr=$4
	local sport=$5
	local dport=$6
	local proto=$7
	local qosprio=$8
	local dscpprio=$9
	local NFT_QOS_TMP_TEXT="oifname br-lan"
	local NFT_QOS_TMP_TEXT0=""

	[ -n "$smacaddr" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ether saddr $smacaddr"
	}
	[ -n "$dmacaddr" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ether daddr $dmacaddr"
	}
	[ -n "$sipaddr" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ip saddr $sipaddr"
	} 
	[ -n "$dipaddr" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ip daddr {$dipaddr}"
	} 
	[ -n "$proto" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ip protocol $proto"
	}
	[ -n "$dscpprio" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT ip dscp set $dscpprio"
	}
	[ -n "$qosprio" ] && {
		NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT meta mark set 0x111100$qosprio$qosprio"
	}
	if [ -n "$proto" ]; then
		[ -n "$sport" ] && {
			if [[ "$proto" == "tcp"  ||  "$proto" == "udp" ]]; then
				NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT $proto sport $sport"		
			fi
		}
		[ -n "$dport" ] && {
			if [[ "$proto" == "tcp"  ||  "$proto" == "udp" ]]; then
				NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT $proto sport $dport"		
			fi
		}
	elif [ -n "$sport" ] || [ -n "$dport" ]; then
		 NFT_QOS_TMP_TEXT0="$NFT_QOS_TMP_TEXT"
		[ -n "$sport" ] && {
			NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT tcp sport $sport"
			NFT_QOS_TMP_TEXT0="$NFT_QOS_TMP_TEXT0 udp sport $sport"
		}
		[ -n "$dport" ] && {
			NFT_QOS_TMP_TEXT="$NFT_QOS_TMP_TEXT tcp dport $dport"
			NFT_QOS_TMP_TEXT0="$NFT_QOS_TMP_TEXT0 udp dport $dport"
		}
	fi
	qosdef_appendx "\t\t$NFT_QOS_TMP_TEXT\n"
	[ -n "$NFT_QOS_TMP_TEXT0" ] && {
		qosdef_appendx "\t\t$NFT_QOS_TMP_TEXT0\n"
	}
}
# qosdef_append_rule_{MATCH}_{STATEMENT}
qosdef_append_rule_mac_limit() { # <macaddr> <operator> <unit> <rate>
	local macaddr=$1
	local operator=$2
	local unit=$3
	local rate=$4

	qosdef_appendx \
	    "\t\tether $operator $macaddr limit rate over $rate $unit/second drop\n"
}

# qosdef_append_rule_{MATCH}_{POLICY}
qosdef_append_rule_ip_policy() { # <operator> <ipaddr> <policy>
	qosdef_appendx "\t\tip $1 $2 $3\n"
}

_handle_limit_whitelist() { # <value> <chain>
	local ipaddr=$1
	local operator

	[ -z "$ipaddr" ] && return

	case "$2" in
		download) operator="daddr";;
		upload) operator="saddr";;
	esac

	qosdef_append_rule_ip_policy $operator $ipaddr accept
}

qosdef_append_rule_limit_whitelist() { # <chain>
	config_list_foreach default limit_whitelist _handle_limit_whitelist $1
}

qosdef_flush_table() { # <family> <table>
	nft flush table $1 $2 2>/dev/null
}

qosdef_remove_table() { # <family> <table>
	nft delete table $1 $2 2>/dev/null
}

qosdef_init_header() { # add header for nft script
	qosdef_appendx "#!/usr/sbin/nft -f\n"
	qosdef_appendx "# Copyright @ 2023 Triductor Technology(Suzhou) Inc. - http://www.triductor.com/\n"
	qosdef_appendx "#\n\n"
}

qosdef_init_env() {
	# check interface type of lan
	local lt="$(uci_get "network.lan.type")"
	[ "$lt" = "bridge" ] && export NFT_QOS_HAS_BRIDGE="y"

	# check if ipv6 support
	[ -e /proc/sys/net/ipv6 ] && export NFT_QOS_INET_FAMILY="inet"
}

qosdef_clean_cache() {
	rm -f $NFT_QOS_SCRIPT_FILE
}

qosdef_init_done() {
	echo -e $NFT_QOS_SCRIPT_TEXT > $NFT_QOS_SCRIPT_FILE 2>/dev/null
}

qosdef_start() {
	nft -f $NFT_QOS_SCRIPT_FILE 2>/dev/null
	eval "cs_cli /home/cli/api/protocol/cfe/lrn/lrn_flush 2>/dev/null"	
}
