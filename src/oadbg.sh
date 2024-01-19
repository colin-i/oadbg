#!/bin/bash

#GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 GTK_DEBUG=all GTK_INSPECTOR_DISPLAY=:1 ./oadbg
#"touchscreen" is only available when building GTK with G_ENABLE_DEBUG. See GTK_DEBUG=help
#	but there is a "simulate touchscreen" option at the inspector

GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 ./oadbg

#this can be debugged with: sudo gdb -p pid_of_oadbg
