#
# Copyright (C) 2009-2010 Jo-Philipp Wich <xm@subsignal.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nvram
PKG_RELEASE:=11

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

PKG_FLAGS:=nonshared

include $(INCLUDE_DIR)/package.mk

define Package/nvram
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=Userspace port of the Broadcom NVRAM manipulation tool
  MAINTAINER:=Jo-Philipp Wich <xm@subsignal.org>
  DEPENDS:=@(TARGET_bcm47xx||TARGET_bcm53xx||TARGET_ath79||TARGET_tr6560)
endef

define Package/nvram/description
 This package contains an utility to manipulate NVRAM on Broadcom based devices.
 It works on bcm47xx (Linux 2.6) without using the kernel api.
endef

define Build/Configure
endef

ifeq ($(CONFIG_PACKAGE_nand-utils),y)
	TARGET_CFLAGS += -DNAND
endif

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Wall" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/nvram/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nvram $(1)/usr/sbin/
ifneq ($(CONFIG_TARGET_bcm47xx),)
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nvram-bcm47xx.init $(1)/etc/init.d/nvram
endif
ifneq ($(CONFIG_TARGET_bcm53xx),)
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nvram-bcm53xx.init $(1)/etc/init.d/nvram
endif
endef

$(eval $(call BuildPackage,nvram))
