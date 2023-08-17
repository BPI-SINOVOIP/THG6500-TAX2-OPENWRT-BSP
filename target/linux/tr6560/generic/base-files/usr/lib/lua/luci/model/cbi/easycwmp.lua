--[[
LuCI model for easycwmp configuration management
Copyright PIVA Software <pivasoftware.com>
]]--

local datatypes = require("luci.cbi.datatypes")

m = Map("easycwmp", "tr-069 client",
    [[easycwmpd is a tr-069 client, from <a href='https://www.pivasoftware.com'>
 PIVA Software</a>.
 Note, OpenWrt has mostly complete UCI support for easycwmpd, but this LuCI applet
 only covers a few of those options. In particular, there is very little/no validation
 or help.
See /etc/config/easycwmp for manual configuration.
 ]])
 
s = m:section(TypedSection, "local", "Local settings")
s.anonymous = true
p = s:option(Flag, "enable", "enable")
p = s:option(Value, "interface", "interface")
p = s:option(Value, "port", "port")
p = s:option(Value, "ubus_socket", "ubus_socket")
p = s:option(Value, "date_format", "date_format")
p = s:option(Value, "username", "username")
p = s:option(Value, "password", "password")
p = s:option(Value, "provisioning_code", "provisioning_code")
p = s:option(ListValue, "authentication", "authentication")
p.default = "Digest"
p:value("Digest", "Digest")
p:value("Basic", "Basic")
p = s:option(Value, "session_timeout", "session_timeout")
p = s:option(ListValue, "logging_level", "logging_level")
p.default = "3"
p:value("0", "Critic")
p:value("1", "Warning")
p:value("2", "Notice")
p:value("3", "Info")
p:value("4", "Debug")
p = s:option(Flag, "periodic_check_notify_enable", "periodic_check_notify_enable")
p = s:option(Value, "periodic_check_notify_interval", "periodic_check_notify_interval")

s = m:section(TypedSection, "acs", "ACS settings")
s.anonymous = true
p = s:option(Value, "url", "url")
p = s:option(Value, "username", "username")
p = s:option(Value, "password", "password")
p = s:option(Flag, "periodic_enable", "periodic_enable")
p = s:option(Value, "periodic_interval", "periodic_interval")
p = s:option(Value, "periodic_time", "periodic_time")
p = s:option(Flag, "alias_support", "alias_support")
p = s:option(Flag, "changedustate_enable", "changedustate_enable")
p = s:option(Flag, "http100continue_disable", "http100continue_disable")
p = s:option(Value, "ssl_verify", "ssl_verify")
p = s:option(Value, "ssl_cacert", "ssl_cacert")
p = s:option(Value, "ssl_cert", "ssl_cert")
p = s:option(Value, "retry_min_wait_interval", "retry_min_wait_interval")
p = s:option(Value, "retry_interval_multiplier", "retry_interval_multiplier")
p = s:option(ListValue, "http_compression", "http_compression")
p.default = "Disabled"
p:value("Enabled", "Enabled")
p:value("Disabled", "Disabled")

p = s:option(Value, "heart_interval", "heart_interval")
p = s:option(Value, "heart_time", "heart_time")
p = s:option(Flag, "heart_enable", "heart_enable")
p = s:option(Value, "cwmp_version", "cwmp_version")

s = m:section(TypedSection, "lwn", "Light Weight Notification settings")
s.anonymous = true
p = s:option(Flag, "enable", "enable")
p = s:option(Value, "hostname", "hostname")
p = s:option(Value, "port", "port")

s = m:section(TypedSection, "inform_forced", "Forced Inform Parameters")
s.anonymous = true
p = s:option(DynamicList, "parameter", "parameter")

s = m:section(TypedSection, "notifications_forced", "Forced Notification Parameters")
s.anonymous = true
p = s:option(DynamicList, "active", "active")
p = s:option(DynamicList, "passive", "passive")

s = m:section(TypedSection, "notifications", "Notification Parameters")
s.anonymous = true
p = s:option(DynamicList, "active", "active")
p = s:option(DynamicList, "passive", "passive")

return m
