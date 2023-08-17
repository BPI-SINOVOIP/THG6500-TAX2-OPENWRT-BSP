REQUIRE_IMAGE_METADATA=1
CI_UBIPART="rootfs_data"
ROOTFS_DATA_DEV=$(find_mtd_part $CI_UBIPART)

find_char_mtd_part() {
	local INDEX=$(find_mtd_index "$1")
	local PREFIX=/dev/mtd

	[ -d /dev/mtd ] && PREFIX=/dev/mtd/
	echo "${INDEX:+$PREFIX$INDEX}"
}

platform_do_upgrade() {
	local flag="$(cat /proc/mtd | grep kernelA | wc -l)"
	UPG_DEV_CHAR=$(find_char_mtd_part upgflag)
	UPG_DEV=$(find_mtd_part upgflag)
	if [ "$flag" = "0" ]; then
		PART_NAME=firmwareB
		FIRMWARE_DEV=$(find_char_mtd_part ${PART_NAME})
		mtd erase ${FIRMWARE_DEV}
		default_do_upgrade "$1"
		mtd erase ${UPG_DEV_CHAR}
		echo B > ${UPG_DEV}
	elif [ "$flag" = "1" ]; then
		PART_NAME=firmwareA
		FIRMWARE_DEV=$(find_char_mtd_part ${PART_NAME})
		mtd erase ${FIRMWARE_DEV}
		default_do_upgrade "$1"
		mtd erase ${UPG_DEV_CHAR}
		echo A > ${UPG_DEV}
	else
		echo "dual-firmware startup error"
		exit 1
	fi

	if [ -z "$NO_REBOOT" -o "$NO_REBOOT" != "1" ]; then
	if [ -z "$UPGRADE_BACKUP" ];then
		MTD_index=$(find_mtd_index ${CI_UBIPART})
		MTD_DEV=mtdblock${MTD_index}
		SIZE=$(cat /proc/partitions | grep $MTD_DEV | awk -F' ' '{print $3}')
		dd if=/dev/zero of="$ROOTFS_DATA_DEV" bs=1k count=$SIZE
		echo "erase conffiles successful"
	fi
	fi
}

platform_check_image() {
	local magic="$(get_magic_long "$1")"

	[ "$#" -gt 1 ] && return 1

	[ "$magic" != "d00dfeed" -a "$magic" != "27051956" ] && {
		echo "Invalid image type."
		return 1
	}
	return 0
}

platform_copy_config() {
	local magic
	[ -f "$UPGRADE_BACKUP" ] && {
		magic="$(get_magic_long $DATA_DEV cat)"
		if [ "$magic" = "55424923" ]; then
			# ubi config restore to backup partition, no support
			nand_restore_config $UPGRADE_BACKUP
			# sync
			echo "ubifs conffiles successful"
		else
			sync
			echo "sysupgrade conffiles successful"
		fi
	}
}
