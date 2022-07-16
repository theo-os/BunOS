#!/bin/sh
set -ex

sudo mount --bind /proc ./sysroot/proc
sudo mount --bind /dev ./sysroot/dev
sudo mount --bind /sys ./sysroot/sys
