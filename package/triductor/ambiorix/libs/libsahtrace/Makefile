include $(TOPDIR)/rules.mk

PKG_NAME:=libsahtrace
PKG_VERSION:=v1.12.0
SHORT_DESCRIPTION:=Small and flexible library to enable tracing and logging

PKG_SOURCE:=libsahtrace-v1.12.0.tar.gz
PKG_SOURCE_URL:=https://gitlab.com/prpl-foundation/components/core/libraries/libsahtrace/-/archive/v1.12.0
PKG_HASH:=87feafa15d7b9d6702ad81b2db4100750a9d5a856e088a9ff6797452f9d6a0c3
PKG_BUILD_DIR:=$(BUILD_DIR)/libsahtrace-v1.12.0
PKG_MAINTAINER:=Soft At Home <support.opensource@softathome.com>
PKG_LICENSE:=BSD-2-Clause-Patent
PKG_LICENSE_FILES:=LICENSE

PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  CATEGORY:=pcb
  SUBMENU:=Libraries
  TITLE:=$(SHORT_DESCRIPTION)
  URL:=https://gitlab.com/prpl-foundation/components/core/libraries/libsahtrace
  MENU:=1
endef

define Package/$(PKG_NAME)/description
	Small and flexible library to enable tracing and logging
endef

define Build/Compile
	$(call Build/Compile/Default, STAGINGDIR=$(STAGING_DIR) CONFIGDIR=$(STAGING_DIR) PKG_CONFIG_PATH=$(STAGING_DIR)/usr/lib/pkgconfig RAW_VERSION=$(PKG_VERSION) HARDCO_HAL_DIR=$(STAGING_DIR)/usr/include CONFIG_SAH_TRACES_ENABLED=$(CONFIG_SAH_TRACES_ENABLED) CONFIG_SAH_TRACES_LEVEL=$(CONFIG_SAH_TRACES_LEVEL) CONFIG_SAH_TRACES_SYSLOG_CONSOLE=$(CONFIG_SAH_TRACES_SYSLOG_CONSOLE) CONFIG_SAH_TRACE_NO_COLORS=$(CONFIG_SAH_TRACE_NO_COLORS))
endef

define Build/Install
	$(call Build/Install/Default, install INSTALL=install D=$(PKG_INSTALL_DIR) DEST=$(PKG_INSTALL_DIR) CONFIGDIR=$(STAGING_DIR) PV=$(PKG_VERSION) PKG_CONFIG_LIBDIR=$(STAGING_DIR)/usr/lib/pkgconfig LIBDIR=/usr/lib INSTALL_LIB_DIR=/lib INSTALL_BIN_DIR=/bin RAW_VERSION=$(PKG_VERSION) HARDCO_HAL_DIR=$(STAGING_DIR)/usr/include CONFIG_SAH_TRACES_ENABLED=$(CONFIG_SAH_TRACES_ENABLED) CONFIG_SAH_TRACES_LEVEL=$(CONFIG_SAH_TRACES_LEVEL) CONFIG_SAH_TRACES_SYSLOG_CONSOLE=$(CONFIG_SAH_TRACES_SYSLOG_CONSOLE) CONFIG_SAH_TRACE_NO_COLORS=$(CONFIG_SAH_TRACE_NO_COLORS))
	find $(PKG_INSTALL_DIR) -name *.a -exec rm {} +;
	find $(PKG_INSTALL_DIR) -name *.h -exec rm {} +;
	find $(PKG_INSTALL_DIR) -name *.pc -exec rm {} +;
endef

define Build/InstallDev
	$(call Build/Install/Default, install INSTALL=install D=$(STAGING_DIR) DEST=$(STAGING_DIR) CONFIGDIR=$(STAGING_DIR) PV=$(PKG_VERSION) PKG_CONFIG_LIBDIR=$(STAGING_DIR)/usr/lib/pkgconfig LIBDIR=/usr/lib INSTALL_LIB_DIR=/lib INSTALL_BIN_DIR=/bin RAW_VERSION=$(PKG_VERSION) HARDCO_HAL_DIR=$(STAGING_DIR)/usr/include CONFIG_SAH_TRACES_ENABLED=$(CONFIG_SAH_TRACES_ENABLED) CONFIG_SAH_TRACES_LEVEL=$(CONFIG_SAH_TRACES_LEVEL) CONFIG_SAH_TRACES_SYSLOG_CONSOLE=$(CONFIG_SAH_TRACES_SYSLOG_CONSOLE) CONFIG_SAH_TRACE_NO_COLORS=$(CONFIG_SAH_TRACE_NO_COLORS))
endef

define Package/$(PKG_NAME)/install
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
	if [ -d ./files ]; then \
		$(CP) ./files/* $(1)/; \
	fi
endef

define Package/$(PKG_NAME)/config
	source "$(SOURCE)/Config.in"
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
