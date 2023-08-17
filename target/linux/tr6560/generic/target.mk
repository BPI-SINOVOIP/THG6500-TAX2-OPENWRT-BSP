# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2006-2022  triductor


ARCH:=arm
BOARDNAME:=Generic
CPU_TYPE:=cortex-a9
KERNELNAME:=zImage
FEATURES+= nand
DEFAULT_PACKAGES += ubifs

define Target/Description
	Build firmware images for Triductor TR6560 Generic ARM based boards.
endef
