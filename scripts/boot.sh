#!/bin/sh

mkdir -p sysroot/{dev,proc,sys,run,tmp}

zig cc -static -target native-linux-musl -lc -o sysroot/bin/init init.c

sudo sh ./scripts/mkimage.sh

qemu-system-x86_64 \
	-hda os.img \
	-m 1024 \
	-serial stdio \
	-cpu host \
	-accel kvm

