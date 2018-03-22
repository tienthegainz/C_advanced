#!/bin/bash


libfdr="home/blahblah/.../libfdr"; #duong dan den thu muc chua libfdr

filepath=$PWD/;
fileIn=$filepath$(echo $1| cut -d'.' -f 1);
fileOut=$filepath$2;

echo "$fileIn"

cext=".c";
oext=".o";

if [ -f $fileIn$cext ]; then
gcc -g -I/$libfdr -c $fileIn$cext
gcc -g -o $fileOut $fileIn$oext /$libfdr/libfdr.a
else
echo "File not found!"
fi

#code by QLK_Dragon