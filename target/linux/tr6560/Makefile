# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2006-2022  triductor

include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=tr6560
BOARDNAME:=triductor TR6560
SUBTARGETS:=generic virgo
FEATURES:=squashfs

KERNEL_PATCHVER:=5.10
KERNEL_TESTING_PATCHVER:=5.10

KERNELNAME:=bzImage

include $(INCLUDE_DIR)/target.mk

# 开源wifi相关package
# 开源luci相关package
# 开源工具package
# 开源内核package
# easycwmp相关package
# triductor自研package
DEFAULT_PACKAGES += hostapd-utils wireless-tools wpad-basic-wolfssl wpa-cli uledd getopt\
luci luci-compat luci-ssl luci-app-omcproxy\
conntrack ethtool ip-bridge lftp memtester nand-utils nvram tcpdump xl2tpd udhcpsnoop\
kmod-gpio-button-hotplug kmod-leds-gpio \
dmc easycwmp \
start-boot_6560 triboot kmod-kgpio_adapter kmod-igmp_mdb_notify tri_bsp cs_cli luci-app-triqos trinft-qos firewall4br\
libamxb  mod-amxb-ubus prplmesh  meshinfo

$(eval $(call BuildTarget))

