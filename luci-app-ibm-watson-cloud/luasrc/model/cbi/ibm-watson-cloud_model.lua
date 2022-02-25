map = Map("ibm-watson-cloud", "IBM Watson Cloud")

main_sct = map:section(NamedSection, "main_sct", "ibm-watson-cloud")
enable = main_sct:option(Flag, "enable", "Enable", "Enable program")
interval = main_sct:option(Value, "interval", "Interval", "Data update interval")
interval.datatype = "uinteger"

device_sct = map:section(NamedSection, "device_sct", "ibm-watson-cloud", "Device Configuration")
org = device_sct:option(Value, "org", "Organization")
type = device_sct:option(Value, "type", "Device type")
device = device_sct:option(Value, "device", "Device")
auth = device_sct:option(Value, "auth", "Authorization token");

return map