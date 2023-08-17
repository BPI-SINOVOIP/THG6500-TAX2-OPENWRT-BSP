#!/bin/sh

uci set wireless.radio0.disabled='0'
uci set wireless.radio1.disabled='0'
uci commit
wifi up