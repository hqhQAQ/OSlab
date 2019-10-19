CROSS_COMPILE = riscv64-unknown-linux-gnu-
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

INCLUDE = 	-I$(srctree)/arch/riscv/include \
		-I$(srctree)/include

CFLAGS = -g -mcmodel=medany -ffunction-sections -fdata-sections $(INCLUDE)
ASFLAGS = -g

obj = vmlinux
TOP_DIR = $(PWD)

LDS = -T$(TOP_DIR)/arch/riscv/kernel/vmlinux.lds

srctree = $(TOP_DIR)
objtree = $(TOP_DIR)


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
export ASFLAGS

all : $(obj)
$(obj):
	$(MAKE) -C init
	$(MAKE) -C lib
	$(MAKE) -C arch/riscv
	$(LD) $(LDS) -o $(TOP_DIR)/$(obj) arch/riscv/kernel/head.o arch/riscv/kernel/mtrap.o init/main.o lib/std.a
	$(NM) -n $(obj) | grep -v '\( [aNUw] \)\|\(__crc_\)\|\( \$[adt]\)\|\( .L\)' > System.map

.PHONY:clean
clean:
	-rm -f $(TOP_DIR)/$(obj)
	-rm -f $(TOP_DIR)/System.map 
	-$(MAKE) -C arch/riscv clean
