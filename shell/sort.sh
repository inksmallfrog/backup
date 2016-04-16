#!/bin/zsh
#sort
rm -f /tmp/sorted
sort $1 > /tmp/sorted
cp /tmp/sorted $1
rm -f /tmp/sorted
exit 0
