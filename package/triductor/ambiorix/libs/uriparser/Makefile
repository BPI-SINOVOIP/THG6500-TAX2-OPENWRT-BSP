include $(TOPDIR)/rules.mk

PKG_NAME:=uriparser
PKG_VERSION:=0.9.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/$(PKG_NAME)/$(PKG_NAME)/releases/download/$(PKG_NAME)-$(PKG_VERSION)/
PKG_HASH:=6cef39d6eaf1a48504ee0264ce85f078758057dafb1edd0a898183b55ff76014

PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=COPYING

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=libs
	CATEGORY:=ambiorix
	SUBMENU:=Libraries
	TITLE:=RFC 3986 compliant URI parsing and handling library
	URL:=https://uriparser.github.io/
endef

define Package/$(PKG_NAME)/description
	Uriparser is a strictly RFC 3986 compliant URI parsing and handling library written in C89 ("ANSI C"). Uriparser is cross-platform, fast, supports Unicode, and is licensed under the New BSD license.
endef

CMAKE_OPTIONS += -DURIPARSER_BUILD_DOCS:BOOL=OFF -DURIPARSER_BUILD_TESTS:BOOL=OFF

define Build/Install
	$(call Build/Install/Default)
	find $(PKG_INSTALL_DIR) -name *.cmake -exec rm {} +;
	find $(PKG_INSTALL_DIR) -name *.h -exec rm {} +;
	find $(PKG_INSTALL_DIR) -name *.pc -exec rm {} +;
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/uriparser
	$(CP) $(PKG_BUILD_DIR)/include/uriparser $(STAGING_DIR)/usr/include/
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/*.so* $(STAGING_DIR)/usr/lib/
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib/pkgconfig
	$(CP) $(PKG_BUILD_DIR)/*.pc $(STAGING_DIR)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
