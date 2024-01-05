#
# Copyright (C) 2018 rosysong@rosinson.com
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=trinft-qos
PKG_VERSION:=1.0.6
PKG_RELEASE:=4
PKG_LICENSE:=GPL-2.0

PKG_MAINTAINER:=Rosy Song <rosysong@rosinson.com>

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/trinft-qos
  SECTION:=utils
  CATEGORY:=Triductor
  DEPENDS:=+kmod-nft-netdev +kmod-nft-bridge +nftables
  TITLE:=Triductor QoS scripts over nftables
  PKGARCH:=all
endef

define Package/trinft-qos/description
 This package provides implementation for qos over nftables.
 Currently, static/dynamic qos and traffic shaping are supported.
endef

define Package/trinft-qos/conffiles
/etc/config/nft-qos
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/trinft-qos/install
	$(INSTALL_DIR) $(1)/lib/nft-qos
	$(INSTALL_DATA) ./files/lib/* $(1)/lib/nft-qos/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/nft-qos.config $(1)/etc/config/nft-qos
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nft-qos.init $(1)/etc/init.d/nft-qos
endef

$(eval $(call BuildPackage,trinft-qos))
