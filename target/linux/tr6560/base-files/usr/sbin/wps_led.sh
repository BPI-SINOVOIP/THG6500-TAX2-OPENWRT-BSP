#!/bin/sh

case "$1" in
    "on")
        ubus call led set '{ "leds": { "tri:green:wps": 255 }, "on": 5000 }'
    ;;
    "off")
        ubus call led set '{ "leds": { "tri:green:wps": 0 } }'
    ;;
    "blink")
        ubus call led set '{ "leds": { "tri:green:wps": [0, 255] }, "on":250, "off":250, "blink":1 }'
    ;;
esac