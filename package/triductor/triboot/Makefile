#
# Makefile for triductor bootloader
#
#

include $(TOPDIR)/rules.mk

PKG_NAME:= tri_boot
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)


include $(INCLUDE_DIR)/package.mk


    
define Package/triboot
  CATEGORY:=Triductor
  TITLE:= Triductor TR6560  Bootloader
  MAINTAINER:= rlsha@triductor.com
  DEPENDS:=
endef

define Package/triboot/description
 This package contains triductor bootram code 
endef



define Build/Prepare
	@if [ ! -d release ]; then \
		$(CP) ./* $(PKG_BUILD_DIR)/ ; \
    fi
endef

define Build/Configure
endef

REL_TIME=$(shell date +"%Y%m%d%H%M")


define Build/Compile
	@if [ ! -d release ]; then \
	echo "----------Build 6560  boot image ----------" ; \
	echo "----------Install 6560 boot image ----------" ; \
	fi
endef

define Package/triboot/install
	@if [ ! -d release ]; then \
	echo "----------Build 6560  boot image $(PROJECT_BOARD) ----------" ; \
    fi
endef

define Build/InstallDev
endef

$(eval $(call BuildPackage,triboot))
