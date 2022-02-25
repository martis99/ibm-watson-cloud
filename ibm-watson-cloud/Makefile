include $(TOPDIR)/rules.mk

PKG_NAME:=ibm-watson-cloud
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/ibm-watson-cloud
	CATEGORY:=Base system
	TITLE:=IBM Watson Cloud
	DEPENDS:=+libibm-watson-iot-c +libopenssl +libubus +libubox +libblobmsg-json
endef

define Package/ibm-watson-cloud/description
	IBM Watson Cloud application
endef

define Package/ibm-watson-cloud/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ibm-watson-cloud $(1)/usr/bin
	$(INSTALL_BIN) ./files/ibm-watson-cloud.init $(1)/etc/init.d/ibm-watson-cloud
	$(INSTALL_CONF) ./files/ibm-watson-cloud.config $(1)/etc/config/ibm-watson-cloud
endef

$(eval $(call BuildPackage,ibm-watson-cloud))