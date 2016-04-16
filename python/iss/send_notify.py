#!/usr/bin/env python
#-*-coding:utf-8-*-

import os

def send_notify(message):
    notify_avator = "/home/inksmallfrog/picture/notify-avator.jpg"
    call_cmd = "notify-send -i " + notify_avator + " \"" + message + "\""
    os.system(call_cmd)
    return None
