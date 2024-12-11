TARGET_MODULE := simple-module

# If we are using the kernel build system
ifneq ($(KERNELRELEASE),)
    $(TARGET_MODULE)-objs := main.o
    obj-m := $(TARGET_MODULE).o

# If we are not using the kernel build system (i.e., from the command line)
else
    BUILDSYSTEM_DIR := /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

all:
	# Build the module using the kernel build system
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules

clean:
	# Clean up generated files
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean

load:
	# Load the module
	insmod ./$(TARGET_MODULE).ko

unload:
	# Unload the module
	rmmod ./$(TARGET_MODULE).ko

endif
