#!/bin/sh
list="$(ldd ./sysroot/bin/bun | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp -v --parents "$i" "sysroot"; done

mkdir -p ./sysroot/usr/lib
cp -va ./lib/* ./sysroot/usr/lib/
cp -va /lib/libgcc_s.so.1 ./sysroot/usr/lib/

