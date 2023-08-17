#!/bin/sh

. $TOPDIR/scripts/functions.sh

part=""
ubinize_param=""
outfile=""
err=""
ubinize_seq=""

ubivol() {
    volid=$1
    name=$2
    image=$3
    autoresize=$4
    size="$5"
    echo "[$name]"
    echo "mode=ubi"
    echo "vol_id=$volid"
    echo "vol_name=$name"
    if [ "$image" ]; then
        echo "image=$image"
        [ -n "$size" ] && echo "vol_size=${size}"
    else
        echo "vol_size=1MiB"
    fi
    if [ "$autoresize" ]; then
        echo "vol_type=dynamic"
        echo "vol_flags=autoresize"
    else
        echo "vol_type=static"
        echo "vol_flags=skip-check"
    fi
    echo "vol_alignment=1"
}

ubilayout() {
	local vol_id=0
	local rootsize=
	local autoresize=

	for part in $parts; do
		name="${part%%=*}"
		prev="$part"
		part="${part#*=}"
		[ "$prev" = "$part" ] && part=$part

		if [ "$name" = "rootfs_data" ]; then
			ubiimg="$( mktemp 2> /dev/null )"
			mkfsubifs="$( command -v mkfs.ubifs )"
			if [ -x "${mkfsubifs}" ]; then
			    ${mkfsubifs} -r $part -m 2048 -o $ubiimg -e 126976 -c 776 -l 4 -p 2 -x none
			    part=$ubiimg			    
			fi
			
		fi

		size=`ls -l $part | awk '{print $5}'`
		size=`expr $size / 1024`
		# size of LEB
		image=$part

		ubivol $vol_id "$name" "$image" "1" "${size}KiB"
		vol_id=$(( $vol_id + 1 ))
	done
}

set_ubinize_seq() {
	if [ -n "$SOURCE_DATE_EPOCH" ] ; then
		ubinize_seq="-Q $SOURCE_DATE_EPOCH"
	fi
}

while [ "$1" ]; do
	case "$1" in
	"--part")
		parts="$parts $2"
		shift
		shift
		continue
		;;
	"-"*)
		ubinize_param="$@"
		break
		;;
	*)
		if [ ! "$outfile" ]; then
			outfile=$1
			shift
			continue
		fi
		;;
	esac
done

if [ ! "$outfile" ]; then
	echo "syntax: $0 [--part <name>=<file>] out [ubinize opts]"
	exit 1
fi

ubinize="$( command -v ubinize )"
if [ ! -x "$ubinize" ]; then
	echo "ubinize tool not found or not usable"
	exit 1
fi

ubinizecfg="$( mktemp 2> /dev/null )"
if [ -z "$ubinizecfg" ]; then
	# try OSX signature
	ubinizecfg="$( mktemp -t 'ubitmp' )"
fi
ubilayout > "$ubinizecfg"

set_ubinize_seq
cat "$ubinizecfg"
${ubinize} $ubinize_seq -o "$outfile" $ubinize_param "$ubinizecfg" -v
err="$?"
[ ! -e "$outfile" ] && err=2
rm "$ubinizecfg"

exit $err
