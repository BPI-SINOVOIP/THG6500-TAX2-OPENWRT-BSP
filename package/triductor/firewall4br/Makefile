#
# Copyright (C) 2021 Jo-Philipp Wich <jo@mein.io>
#

include $(TOPDIR)/rules.mk

PKG_NAME:=firewall4br
PKG_VERSION:=1.0


include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  CATEGORY:=Triductor
  TITLE:=OpenWrt 4th gen firewall for bridge
  DEPENDS:=
endef

define Package/$(PKG_NAME)/description
 This package provides an nftables-based implementation of the UCI firewall
 sharing the same configuration format.
endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) ./files/etc/init.d/firewall4br $(1)/etc/init.d/
	$(INSTALL_CONF) ./files/etc/config/firewall4br $(1)/etc/config/
endef

define Build/Compile
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
