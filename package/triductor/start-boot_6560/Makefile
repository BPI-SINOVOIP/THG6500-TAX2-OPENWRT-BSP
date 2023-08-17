#
# Makefile for triductor bootloader
#
#

include $(TOPDIR)/rules.mk

PKG_NAME:= start-boot_6560
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)


include $(INCLUDE_DIR)/package.mk


    
define Package/start-boot_6560
  CATEGORY:=Triductor
  TITLE:= Triductor First level Bootloader
  MAINTAINER:= rlsha@triductor.com
  DEPENDS:=
endef

define Package/start-boot_6560/description
	This package contains triductor first level boot code
endef



define Build/Prepare
	$(CP) ./* $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/start-boot_6560/install
	$(CP) $(PKG_BUILD_DIR)/*.bin  $(STAGING_DIR_HOST)/bin/
endef

define Build/InstallDev
endef

$(eval $(call BuildPackage,start-boot_6560))
