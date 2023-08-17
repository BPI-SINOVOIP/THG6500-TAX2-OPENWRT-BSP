#
# Makefile for the Linux Wireless network device drivers.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=tr5220
PKG_VERSION:=
PKG_RELEASE:=1.0

PKG_SOURCE:=
PKG_SOURCE_URL:=
PKG_MD5SUM:=

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)

include $(INCLUDE_DIR)/package.mk

define Package/tr5220/Default
  SECTION:=base
  CATEGORY:=Triductor
  SUBMENU:=WiFi
  TITLE:=Driver for Triductor tr5220
  URL:=
  DEPENDS:=+kmod-cfg80211 +@DRIVER_11AC_SUPPORT +@DRIVER_11N_SUPPORT +@DRIVER_11AX_SUPPORT
endef

define Package/tr5220-eFEM
$(call Package/tr5220/Default)
  TITLE += (with external FEM)
  VARIANT:=eFEM
endef

define Package/tr5220-iFEM
$(call Package/tr5220/Default)
  TITLE += (with internal FEM)
  VARIANT:=iFEM
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -R ./files/* $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

autoload_mods_$(SUBTARGET) := peanut_plat \
                              peanut_wifi \
                              wifi_debug

define Package/tr5220/install
	$(INSTALL_DIR) $(1)/$(MODULES_SUBDIR)
	$(INSTALL_DIR) $(1)/etc/wifi
	$(INSTALL_DIR) $(1)/usr/sbin

	$(CP) $(PKG_BUILD_DIR)/ko/*.ko $(1)/$(MODULES_SUBDIR)
	$(call ModuleAutoLoad,tr5220,$(1),06-,,$(autoload_mods_$(SUBTARGET)))
	$(CP) $(PKG_BUILD_DIR)/ko/*.bin $(1)/etc/wifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/* $(1)/etc/wifi/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/* $(1)/usr/sbin/
endef


define Package/tr5220-eFEM/install
$(call Package/tr5220/install,$(1))
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/cfg_vspm3xx_external.ini $(1)/etc/wifi/cfg_vspm3xx.ini
endef

define Package/tr5220-iFEM/install
$(call Package/tr5220/install,$(1))
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/cfg_vspm3xx_internal.ini $(1)/etc/wifi/cfg_vspm3xx.ini
endef


$(eval $(call BuildPackage,tr5220-eFEM))
$(eval $(call BuildPackage,tr5220-iFEM))
