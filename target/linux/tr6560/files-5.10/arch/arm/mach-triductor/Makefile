#
# Makefile for the linux kernel.
#
#ccflags-$(CONFIG_ARCH_MULTIPLATFORM) := -I$(srctree)/$(src)/include \
#	-I$(srctree)/arch/arm/plat-tri/include

ccflags-$(CONFIG_ARCH_MULTIPLATFORM) := -I$(srctree)/$(src)/include \

#obj-y              += watchdog.o
obj-$(CONFIG_SMP)  += platsmp.o

