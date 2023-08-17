#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=triqos-scripts
PKG_VERSION:=1.3.1
PKG_RELEASE:=$(AUTORELEASE)
PKG_LICENSE:=GPL-2.0

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/triqos-scripts
  SECTION:=utils
  CATEGORY:=Triductor
  DEPENDS:=+tc +kmod-sched-core +kmod-sched-connmark +kmod-ifb +iptables +iptables-mod-ipopt +iptables-mod-conntrack-extra
  TITLE:=Triductor QoS scripts
  PKGARCH:=all
endef

define Package/triqos-scripts/description
 A set of scripts that abstract QoS configuration into a simple 
 configuration file supporting stanzas that specify any number of QoS 
 entries.
endef

define Package/triqos-scripts/conffiles
/etc/config/qos
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/triqos-scripts/install
	$(INSTALL_DIR) $(1)
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,triqos-scripts))
