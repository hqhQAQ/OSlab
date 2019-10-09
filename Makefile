CROSS_COMPILE = riscv64-unknown-linux-gnu-
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

CFLAGS = -g

obj = vmlinux
TOP_DIR = $(PWD)
dep = $(TOP_DIR)/arch/riscv/init/main.o \
	  $(TOP_DIR)/arch/riscv/kernel/head.o \
	  $(TOP_DIR)/arch/riscv/kernel/vmlinux.lds 

LDS = $(TOP_DIR)/arch/riscv/kernel/vmlinux.lds

srctree = $(TOP_DIR)
objtree = $(TOP_DIR)

INCLUDE = 	-I$(srctree)/arch/riscv/include/uapi \
			-I$(objtree)/arch/riscv/include/generated/uapi \
			-I$(srctree)/include/uapi \
			-I$(objtree)/include/generated/uapi \
			-I$(srctree)/arch/riscv/include \
			-I$(objtree)/arch/riscv/include/generated \
			-I$(objtree)/include 

export CC
export LD
export AS
export NM
export obj
export src
export TOP_DIR
export dep
export INCLUDE
export LDS
export CFLAGS

$(obj): 
	$(MAKE) -C arch/riscv
	$(LD) -T $(LDS) -o $(TOP_DIR)/$(obj) arch/riscv/kernel/head.o arch/riscv/init/main.o -Map=$(TOP_DIR)/System.map
	cp vmlinux arch/riscv/boot/Image

.PHONY:clean

clean:
	-rm -f $(TOP_DIR)/$(obj)
	-rm -f $(TOP_DIR)/System.map 
	-$(MAKE) -C arch/riscv clean
	rm -f arch/riscv/boot/Image