#!/bin/bash
#########################################################################
# File Name:		push.sh
# Author:			Landerl Young
# e-Mail:			LanderlYoung@gmail.com
# Created Time:		Fri Aug 26 18:35:14 2016
#########################################################################

for file in *.pcm;do
    adb push $file /sdcard/Download/$file
done
