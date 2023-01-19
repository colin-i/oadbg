#!/usr/bin/bash

#if [ -n "${1}" ]; then
#if [ "${1}" = "d" ]; then
#GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 GTK_DEBUG=all GTK_INSPECTOR_DISPLAY=:1 ./oadbg
#"touchscreen" is only available when building GTK with G_ENABLE_DEBUG. See GTK_DEBUG=help
#	but there is a "simulate touchscreen" option at the inspector
#else
#GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 ./oadbg
#fi
#else
#./oadbg
#fi

#will be text:"ping" here and inside oadbg, without read inside oadbg will pe only "ping"
#read -n10 a
#read -n1 a
#echo ${a} > /home/bc/Desktop/1
#if [ "${a}" = "1" ]; then
GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 ./oadbg
#else
#./oadbg
#fi
