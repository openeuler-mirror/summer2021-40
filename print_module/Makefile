#
# Makefile for the linux kernel.
#

# Object file lists.
#

obj-m := print_module.o

KERNELBUILD := ../kernel
CURRENT_PATH := $(shell pwd)
all:
	make -C $(KERNELBUILD) M=$(CURRENT_PATH) modules
clean:
	make -C $(KERNELBUILD) M=$(CURRENT_PATH) clean
