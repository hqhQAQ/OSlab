CROSS_COMPILE = riscv64-unknown-linux-gnu-
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

INCLUDE = 	-I$(srctree)/arch/riscv/include \
			-I$(srctree)/lib/include

CFLAGS = -g -mcmodel=medany -ffunction-sections -fdata-sections $(INCLUDE)
ASFLAGS = -g 

obj = vmlinux
TOP_DIR = $(PWD)

LDS = -T$(TOP_DIR)/arch/riscv/kernel/vmlinux.lds

srctree = $(TOP_DIR)
objtree = $(TOP_DIR)

dependence = 

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

all: main lib kernel vmlinux System.map 

.PHONY:main
main:
	@$(MAKE) --no-print-directory -C init

.PHONY:lib
lib:
	@$(MAKE) --no-print-directory -C lib

.PHONY:kernel
kernel:
	@$(MAKE) --no-print-directory -C arch/riscv

vmlinux:main lib kernel
	@echo LD $@
	@$(LD) $(LDS) -o $(TOP_DIR)/$(obj) arch/riscv/kernel/*.o init/main.o lib/std.a

System.map:vmlinux	
	@echo NM System.map
	@$(NM) -n $(obj) | grep -v '\( [aNUw] \)\|\(__crc_\)\|\( \$[adt]\)\|\( .L\)' > System.map

.PHONY:clean
clean:
	-rm -f $(TOP_DIR)/$(obj)
	-rm -f $(TOP_DIR)/System.map 
	@$(MAKE) --no-print-directory -C arch/riscv clean
	@$(MAKE) --no-print-directory -C init clean
	@$(MAKE) --no-print-directory -C lib clean

.PHONY:run
run:
	qemu-system-riscv64 -nographic -machine virt -kernel vmlinux

.PHONY:debug
debug:
	qemu-system-riscv64 -nographic -machine virt -kernel vmlinux -S -s

.PHONY:gdb
gdb:
	riscv64-unknown-linux-gnu-gdb vmlinux

