typedef struct Device Device;

int device_connect(Device **device, const char* orgId, const char* typeId, const char* deviceId, const char* token);
int device_disconnect(Device *device);
int device_send_data(Device *device, char* data);