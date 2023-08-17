# /bin/sh
. /lib/functions.sh
. /usr/share/libubox/jshn.sh

# 更新A/B版本信息到uci
curversion=$(cat /etc/openwrt_release | grep DISTRIB_RELEASE | cut -d \' -f 2)
echo "curversion=$curversion" > /tmp/dual_version.meta
flag="$(cat /proc/mtd | grep rootfsA | wc -l)"
if [ "$flag" = "1" ]; then
	MTD=rootfsA
else
	MTD=rootfsB
fi

MTD_index=$(find_mtd_index ${MTD})
MTD_DEV=mtdblock${MTD_index}
SIZE=$(cat /proc/partitions | grep $MTD_DEV | awk -F' ' '{print $3}')
index=0
while [ $index -lt $SIZE ]; do
	SEEK=`expr $index \* 1024`
	mtd_debug read /dev/mtd${MTD_index} $SEEK 0x100000 /tmp/meta.test
	cat /tmp/meta.test | grep version > /tmp/version.meta
	rm -rf /tmp/meta.test
	[ -s /tmp/version.meta ] && { break; }
	index=`expr $index + 1024`
done

json_init
json_load "$(cat /tmp/version.meta)"
json_get_var Obj_version version
if [ -n "$Obj_version" ]; then
	json_select version
	json_get_var backversion version
	if [ -n "$backversion" ]; then
		echo "backupversion=${backversion}" >> /tmp/dual_version.meta
	else
		echo "backupversion=${curversion}" >> /tmp/dual_version.meta
	fi
	json_select ..
else
	echo "backupversion=${curversion}" >> /tmp/dual_version.meta
fi
rm -rf /tmp/version.meta