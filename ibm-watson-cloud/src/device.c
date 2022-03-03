#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iotp_device.h>
#include "device.h"

struct Device {
    IoTPConfig *config;
    IoTPDevice *device;
};

void deviceCommandCallback(char *type, char *id, char *commandName, char *format, void *payload, size_t payloadSize) {
    fprintf(stdout, "Received device command:\n");
    fprintf(stdout, "Type=%s ID=%s CommandName=%s Format=%s Len=%d\n", type?type:"", id?id:"", commandName?commandName:"", format?format:"", (int)payloadSize);
    fprintf(stdout, "Payload: %s\n", payload?(char *)payload:"");
}

void logCallback(int level, char *message) {
    if(level > 0) {
        fprintf(stdout, "%s\n", message? message:"NULL");
    }
    fflush(stdout);
}

void MQTTTraceCallback(int level, char *message) {
    if (level > 0) {
        fprintf(stdout, "%s\n", message? message:"NULL");
    }
    fflush(stdout);
}

int device_connect(Device **pDevice, const char* orgId, const char* typeId, const char* deviceId, const char* token) {
    *pDevice = malloc(sizeof(Device));
    Device* device = *pDevice;

    int rc = IOTPRC_SUCCESS;

    device->config = NULL;
    device->device = NULL;

    rc = IoTPConfig_setLogHandler(IoTPLog_FileDescriptor, stdout);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to set log handler rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPConfig_create(&device->config, NULL);
    IoTPConfig_setProperty(device->config, "identity.orgId", orgId);
    IoTPConfig_setProperty(device->config, "identity.typeId", typeId);
    IoTPConfig_setProperty(device->config, "identity.deviceId", deviceId);
    IoTPConfig_setProperty(device->config, "auth.token", token);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to create config rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPDevice_create(&device->device, device->config);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to create device rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPDevice_setMQTTLogHandler(device->device, &MQTTTraceCallback);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to set MQTT log handler rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPDevice_connect(device->device);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to connect rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    IoTPDevice_setCommandsHandler(device->device, deviceCommandCallback);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to set commands handler rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPDevice_subscribeToCommands(device->device, "+", "+");
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to subscribe to commands rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    if(rc == IOTPRC_SUCCESS) {
        fprintf(stdout, "Successfully connected to IBM Watson Cloud\n");
    }

    return 0;
}

int device_disconnect(Device *device) {
    int rc = IOTPRC_SUCCESS;
    
    rc = IoTPDevice_disconnect(device->device);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to diconnect rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPDevice_destroy(device->device);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to destroy device rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    rc = IoTPConfig_clear(device->config);
    if(rc != IOTPRC_SUCCESS) {
        fprintf(stderr, "Failed to clear config rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    if(rc == IOTPRC_SUCCESS) {
         fprintf(stdout, "Successfully disconnected from IBM Watson Cloud\n");
    }

    free(device);
    return 0;
}

int device_send_data(Device *device, char* data) {
    int rc = IOTPRC_SUCCESS;
    fprintf(stdout, "Sending data to IBM Watson Cloud...\n");

    rc = IoTPDevice_sendEvent(device->device,"status", data, "json", QoS0, NULL);
    if(rc == IOTPRC_SUCCESS) {
        fprintf(stdout, "Data was succesfully sent\n");
    } else {
        fprintf(stderr, "Failed to send event rc=%d reason:%s\n", rc, IOTPRC_toString(rc));
        return 1;
    }

    return 0;
}