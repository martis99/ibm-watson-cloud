map = Map("ibm-watson-cloud")

main_sct = map:section(NamedSection, "main_sct", "ibm-watson-cloud", "IBM Watson Cloud")
enable = main_sct:option(Flag, "enable", "Enable", "Enable program")
interval = main_sct:option(Value, "interval", "Interval", "Data update interval")
interval.datatype = "uinteger"
org = main_sct:option(Value, "org", "Organization")
type = main_sct:option(Value, "type", "Device type")
device = main_sct:option(Value, "device", "Device")
auth = main_sct:option(Value, "auth", "Authorization token");

return map
