module("luci.controller.ibm-watson-cloud_controller", package.seeall)

function index()
    entry({"admin", "services", "ibm-watson-cloud_model"}, cbi("ibm-watson-cloud_model"), _("IBM Watson Cloud"), 105);
end