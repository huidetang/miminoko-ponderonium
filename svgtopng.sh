#!/bin/sh
[ "x$1" = "x" ] && exit 1
DIR=$1
for file in `\find $DIR -name '*.svg'`; do
    filename=${file%.*}
    convert -density 1200 ${filename}".svg" ${filename}".png"
done