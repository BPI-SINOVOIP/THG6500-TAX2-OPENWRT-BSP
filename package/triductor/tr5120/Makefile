#
# Makefile for the Linux Wireless network device drivers.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=tr5120
PKG_VERSION:=
PKG_RELEASE:=1.0

PKG_SOURCE:=
PKG_SOURCE_URL:=
PKG_MD5SUM:=

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)

include $(INCLUDE_DIR)/package.mk

define Package/tr5120/Default
  SECTION:=base
  CATEGORY:=Triductor
  SUBMENU:=WiFi
  TITLE:=Driver for Triductor tr5120 devices
  URL:=
  DEPENDS:=+kmod-cfg80211 +@DRIVER_11AC_SUPPORT +@DRIVER_11N_SUPPORT
endef

define Package/tr5120-basic
$(call Package/tr5120/Default)
  TITLE += (basic)
  VARIANT:=basic
endef

define Package/tr5120-dbac
$(call Package/tr5120/Default)
  TITLE += (dbac)
  VARIANT:=dbac
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -R ./files/* $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

autoload_mods_$(SUBTARGET) := hal \
                              alg \
                              dmac \
                              frw \
                              hmac \
                              oal \
                              oam \
                              plat \
                              sdt \
                              wal

define Package/tr5120/install
	$(INSTALL_DIR) $(1)/$(MODULES_SUBDIR)
	$(INSTALL_DIR) $(1)/etc/wifi
	$(INSTALL_DIR) $(1)/usr/sbin

	$(CP) $(PKG_BUILD_DIR)/ko/*.ko $(1)/$(MODULES_SUBDIR)
	$(call ModuleAutoLoad,tr5120,$(1),06-,,$(autoload_mods_$(SUBTARGET)))
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/Total.wdk $(1)/etc/wifi/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/* $(1)/usr/sbin/
endef


define Package/tr5120-basic/install
$(call Package/tr5120/install,$(1))
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/hazel.ini $(1)/etc/wifi/
endef

ifeq ($(BUILD_VARIANT),dbac)
  MODPARAMS.hal := g_l_rf_channel_num=2 g_l_rf_single_tran=0 g_l_rf_fem_switch=5
endif

define Package/tr5120-dbac/install
$(call Package/tr5120/install,$(1))
	$(INSTALL_DIR) $(1)/lib/wifi
	
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config/hazel_dbac.ini $(1)/etc/wifi/hazel.ini
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/dbac.sh $(1)/lib/wifi/
endef

$(eval $(call BuildPackage,tr5120-basic))
$(eval $(call BuildPackage,tr5120-dbac))
