#!/bin/zsh

export DBUS_SESSION_BUS_ADDRESS=$(grep -z DBUS_SESSION_BUS_ADDRESS /proc/$$/environ | cut -d= -f2-)
notify-send "Hi"
