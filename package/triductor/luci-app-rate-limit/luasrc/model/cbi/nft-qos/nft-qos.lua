-- Copyright 2018 Rosy Song <rosysong@rosinson.com>
-- Licensed to the public under the Apache License 2.0.

local uci = require("luci.model.uci").cursor()
local wa = require("luci.tools.webadmin")
local fs = require("nixio.fs")
local ipc = require("luci.ip")

local def_rate_dl = uci:get("nft-qos", "default", "static_rate_dl")
local def_rate_ul = uci:get("nft-qos", "default", "static_rate_ul")
local def_unit_dl = uci:get("nft-qos", "default", "static_unit_dl")
local def_unit_ul = uci:get("nft-qos", "default", "static_unit_ul")

local def_up = uci:get("nft-qos", "default", "dynamic_bw_up")
local def_down = uci:get("nft-qos", "default", "dynamic_bw_down")

local limit_enable = uci:get("nft-qos", "default", "limit_enable")
local limit_mac_enable = uci:get("nft-qos", "default", "limit_mac_enable")
local limit_type = uci:get("nft-qos", "default", "limit_type")
local enable_priority = uci:get("nft-qos", "default", "priority_enable")

local has_ipv6 = fs.access("/proc/net/ipv6_route")

m = Map("nft-qos", translate("Rate Limit"))

--
-- Taboptions
--
s = m:section(TypedSection, "default", translate("Rate Limit Settings"))
s.addremove = false
s.anonymous = true

s:tab("limit", "Limit Rate by Mac")

--
--Static
--
o = s:taboption("limit", Flag, "limit_enable", translate("Limit Enable"), translate("Enable Limit Rate Feature"))
o.default = limit_enable or o.enabled
o.rmempty = false

--
-- Static Limit Rate - Download Rate
--
if limit_enable == "1" and limit_type == "static" then

	x = m:section(TypedSection, "client", translate("Limit Traffic Rate"))
	x.anonymous = true
	x.addremove = true
	x.template = "cbi/tblsection"

	o = x:option(Value, "macaddr", translate("DeviceMAC"))
	o.rmempty = false
	o.datatype = "macaddr"
	--o.datatype = 'list(macaddr)';
	o.placeholder = ('-- add MAC --');
	--wa.cbi_add_knownips(o)
	


	o = x:option(Value, "drate", translate("Download Rate"))
	o.default = def_rate_dl or '0'
	o.size = 4
	o.datatype = "uinteger"

	o = x:option(ListValue, "drunit", translate("Unit"))
	o.default = def_unit_dl or "kbytes"
	--o:value("bytes", "Bytes/s")
	o:value("kbytes", "Kbps")
	--o:value("mbytes", "MBytes/s")

	o = x:option(Value, "urate", translate("Upload Rate"))
	o.default = def_rate_dl or '0'
	o.size = 4
	o.datatype = "uinteger"

	o = x:option(ListValue, "urunit", translate("Unit"))
	o.default = def_unit_dl or "kbytes"
	--o:value("bytes", "Bytes/s")
	o:value("kbytes", "Kbps")
	--o:value("mbytes", "MBytes/s")
end

return m
