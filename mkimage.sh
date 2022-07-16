#!/bin/sh
set -xe

truncate -s 4G ./os.img 

# Make the partition table, partition and set it bootable.
parted --script os.img mklabel msdos mkpart p ext2 1 100% set 1 boot on
 
# Map the partitions from the image file
kpartx -a os.img
 
# sleep a sec, wait for kpartx to create the device nodes
sleep 1
 
# Make an ext2 filesystem on the first partition.
mkfs.ext2 /dev/mapper/loop0p1
 
# Make the mount-point
mkdir -p build/tmp/p1
 
# Mount the filesystem via loopback
mount /dev/mapper/loop0p1 build/tmp/p1
 
# Copy in the files from the staging directory
cp -r sysroot/* build/tmp/p1

limine-deploy /dev/loop0 
 
# Unmount the loopback
umount build/tmp/p1
 
# Unmap the image
kpartx -d os.img
 
# hack to make everything owned by the original user, since it will currently be
# owned by root...
LOGNAME=`who am i | awk '{print $1}'`
LOGGROUP=`groups $LOGNAME | awk '{print $3}'`
chown $LOGNAME:$LOGGROUP -R build os.img

