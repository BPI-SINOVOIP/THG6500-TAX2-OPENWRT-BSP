#!/bin/sh -x

echo $1 $2 $3 $4 $5 $6 $7 $8 $9
cd $1

ADDECC_CMD=./addecc

PAGE_SIZE=2048
FIRST_BOOT_FAC_LEN=128K
BOOT_FAC_LEN=512K
KERNEL_FAC_LEN=8192K
ROOTFS_FAC_LEN=32768K
ROOTFS_DATA_FAC_LEN=$9

shift
ZERO_LEN=$9


dd if=/dev/zero ibs=1k count=$ZERO_LEN | tr "\000" "\377" > fileFF.tmp
cat TR6560-startbootimage.bin fileFF.tmp | head --byte=$FIRST_BOOT_FAC_LEN > fboot_base.tmp
cat fboot_base.tmp TR6560-bootimage.bin fileFF.tmp | head --bytes=$BOOT_FAC_LEN > boot_base.tmp;\
cat $2 fileFF.tmp | head --bytes=$KERNEL_FAC_LEN > kernelA.tmp;\
cat $3 fileFF.tmp | head --bytes=$ROOTFS_FAC_LEN > rootfsA.tmp;\
cat $2 fileFF.tmp | head --bytes=$KERNEL_FAC_LEN > kernelB.tmp;\
cat $3 fileFF.tmp | head --bytes=$ROOTFS_FAC_LEN > rootfsB.tmp;\
cat $7 fileFF.tmp | head --bytes=$ROOTFS_DATA_FAC_LEN > rootfs_data.tmp;\
cat boot_base.tmp kernelA.tmp rootfsA.tmp kernelB.tmp rootfsB.tmp rootfs_data.tmp > $4-factory.tmp

$ADDECC_CMD -i $4-factory.tmp -b 4 -p $PAGE_SIZE -s 64 -o $4-factory.w

cat $4-factory.w | head --byte=${ZERO_LEN}K > $4-$5-$6-BurningImage.bin
mv $4-$5-$6-BurningImage.bin $1/

rm -fr *.tmp *.w

cd -
