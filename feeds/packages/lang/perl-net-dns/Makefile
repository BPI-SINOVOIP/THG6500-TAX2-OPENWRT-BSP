include $(TOPDIR)/rules.mk

PKG_NAME:=perl-net-dns
PKG_VERSION:=1.33
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_NAME:=Net-DNS
PKG_SOURCE:=$(PKG_SOURCE_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://www.net-dns.org/download
PKG_HASH:=5a40e7cf524e4bd2c33cf03b82b47d5308b712083aa5ee180b0b5af54c71fbd2
PKG_BUILD_DIR:=$(BUILD_DIR)/perl/$(PKG_SOURCE_NAME)-$(PKG_VERSION)
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/perl/$(PKG_SOURCE_NAME)-$(PKG_VERSION)

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=MIT
HOST_BUILD_DEPENDS:=perl/host

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include ../perl/perlmod.mk

define Package/perl-net-dns
  SUBMENU:=Perl
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Net::DNS DNS resolver implemented in Perl
  URL:=https://www.net-dns.org/
  DEPENDS:=perl +perlbase-essential +perlbase-io
endef

define Build/Configure
        $(call perlmod/Configure,,)
endef

define Build/Compile
        $(call perlmod/Compile,,)
endef

define Package/perl-net-dns/install
        $(call perlmod/Install,$(1),Net auto/Net)
endef

define Host/Configure
        $(call perlmod/host/Configure,,,)
endef

define Host/Compile
        $(call perlmod/host/Compile,,)
endef

define Host/Install
        $(call perlmod/host/Install,$(1),)
endef

$(eval $(call BuildPackage,perl-net-dns))
$(eval $(call HostBuild))
