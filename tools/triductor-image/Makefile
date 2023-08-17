# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=triductor-image
PKG_VERSION:=1.0

ADDECC:=addecc

include $(INCLUDE_DIR)/host-build.mk

HOST_CFLAGS += -DMTD_NFC

define Host/Compile
	$(HOSTCC) addecc.c -o $(HOST_BUILD_DIR)/$(ADDECC)
endef

define Host/Install
	cp *.sh $(STAGING_DIR_HOST)/bin/
	cp $(HOST_BUILD_DIR)/$(ADDECC) $(STAGING_DIR_HOST)/bin/addecc
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/$(ADDECC)
endef

$(eval $(call HostBuild))
