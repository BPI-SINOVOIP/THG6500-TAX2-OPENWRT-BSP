#! /bin/sh +x

cd $1

BOOT_FAC_LEN=128K



dd if=/dev/zero ibs=1k count=200 | tr "\000" "\377" > fileFF.tmp;

cat TR6560-bootimage_nodtb.bin fileFF.tmp  | head --bytes=$BOOT_FAC_LEN > TR6560-bootimage.bin.tmp;
cat TR6560-bootimage.bin.tmp boot.dtb   > TR6560-bootimage.bin;
mkdir -p ../bin
mv TR6560-bootimage.bin ../bin/;

rm -f  *.tmp;

cd - > /dev/null;

