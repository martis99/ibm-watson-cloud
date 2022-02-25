include $(TOPDIR)/rules.mk

PKG_NAME:=libibm-watson-iot-c
PKG_RELEASE:=1
PKG_VERSION:=1.0.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/ibm-watson-iot/iot-c.git
PKG_SOURCE_VERSION:=f921dce616af815da2236954c608a2f377c928c5

include $(INCLUDE_DIR)/package.mk

define Package/libibm-watson-iot-c
	CATEGORY:=Libraries
	TITLE:=IBM Watson IoT C library
	DEPENDS:=+libopenssl
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so.1 $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so.1.3 $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTProperties.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTExportDeclarations.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTAsync.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTReasonCodes.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTSubscribeOpts.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/paho.mqtt.c/src/MQTTClientPersistence.h $(1)/usr/include

	$(CP) $(PKG_BUILD_DIR)/build/libiotp-as-device.so $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/build/libiotp-as-device.so.1 $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/build/libiotp-as-device.so.1.0 $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/wiotp/sdk/iotp_device.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/src/wiotp/sdk/iotp_rc.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/src/wiotp/sdk/iotp_utils.h $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/src/wiotp/sdk/iotp_config.h $(1)/usr/include
endef

define Package/libibm-watson-iot-c/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/libiotp-as-device.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/libiotp-as-device.so.1 $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/libiotp-as-device.so.1.0 $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so.1 $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/paho.mqtt.c/build/output/libpaho-mqtt3as.so.1.3 $(1)/usr/lib
endef

$(eval $(call BuildPackage,libibm-watson-iot-c))