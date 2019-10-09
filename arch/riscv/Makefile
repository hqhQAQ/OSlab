$(obj):$(dep)	
	$(LD) -o $(TOP_DIR)/$(obj) kernel/head.o init/main.o -Map=$(TOP_DIR)/System.map
$(TOP_DIR)/arch/riscv/kernel/head.o:
	$(MAKE) -C kernel
$(TOP_DIR)/arch/riscv/init/main.o:
	$(MAKE) -C init

.PHONY:clean
clean:
	-$(MAKE) -C init clean
	-$(MAKE) -C kernel clean
	-rm -f $(TOP_DIR)/$(obj)
	-rm -f $(TOP_DIR)/System.map 