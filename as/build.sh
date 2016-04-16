#!/bin/zsh
#build.sh

if [ $# -lt 1 ]; then
   echo "no parameter"
   exit 0
elif [ $# -ge 1 ]; then
    if [ -f $1 ]; then
	source_name=$1
	object_name=${source_name%.*}.o
	exe_name=${source_name%.*}
	as -gtabs $source_name -o $object_name ;\
	ld $object_name -o $exe_name ;\
	if [ "$2" = "run" ]; then
	    ./$exe_name
	    echo "return code: $?"
	fi
    fi
fi
