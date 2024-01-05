#!/bin/sh
. /usr/share/libubox/jshn.sh

mesh_onboarded=`ubus call uci get '{"config":"prplmesh","section":"config","option":"onboarded"}' | jsonfilter -e "@.value"`
wps_led=`ubus call uci get '{"config":"system","section":"led_wps","option":"sysfs"}' | jsonfilter -e "@.value"`

led_on()
{
    json_init
    json_add_object "leds"
    json_add_int "$wps_led" 255
    json_close_object
    json_add_int "on" $1
    ubus call led set "$(json_dump)"
}

led_off()
{
    json_init
    json_add_object "leds"
    json_add_int "$wps_led" 0
    json_close_object
    ubus call led set "$(json_dump)"
}

led_blink()
{
    json_init
    json_add_object "leds"
    json_add_array "$wps_led"
    json_add_int "" 0
    json_add_int "" 255
    json_close_array
    json_close_object
    json_add_int "on" 250
    json_add_int "off" 250
    json_add_int "blink" 0
    ubus call led set "$(json_dump)"
}

led()
{
    case "$1" in
        "on")
            [ $mesh_onboarded -ne 1 ] && led_on 5000 || led_on 0
        ;;
        "off")
            [ $mesh_onboarded -ne 1 ] && led_off || led_on 0
        ;;
        "blink")
            led_blink
        ;;
    esac
}
