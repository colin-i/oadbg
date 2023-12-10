#!/bin/bash

#GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 GTK_DEBUG=all GTK_INSPECTOR_DISPLAY=:1 ./oadbg
#"touchscreen" is only available when building GTK with G_ENABLE_DEBUG. See GTK_DEBUG=help
#	but there is a "simulate touchscreen" option at the inspector

GDK_BACKEND=broadway BROADWAY_DISPLAY=:0 ./oadbg

#can't debug this:          browser<->(read/write std)oadbg
#make a debugger extension: browser<->(read/write std)elf(read/write socket)<->(read/write socket)oadbg
