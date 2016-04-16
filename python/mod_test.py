#!/usr/bin/env python
#-*-coding:utf-8-*-
########################
#File Name: mod_test.py
#Author: inksmallfrog
#Mail: inksmallfrog@gmail.com
#Created Time: 2016-04-09 09:41:42
########################


def mod_simplify_base(mod):
    base = []
    times = 0
    while(True):
        if(0 == times):
            base.append(10 % mod)
        else:
            base.append(base[times - 1] * base[0])
        if(base[times] > mod / 2):
            base[times] -= mod
        elif(base[times] < -mod / 2):
            base[times] += mod
        for i in range(len(base)):
            if(base[times] == base[i] and times != i):
                return base[:times], i
        times += 1

print mod_simplify_base(11)
