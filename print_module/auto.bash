#!/bin/bash

sudo rmmod print_module.ko
sudo insmod print_module.ko
cat /sys/module/print_module/usedmemory
