$(obj):$(dep)	
	@echo Generate Object File...
$(TOP_DIR)/arch/riscv/kernel/head.o:
	$(MAKE) -C kernel
$(TOP_DIR)/arch/riscv/init/main.o:
	$(MAKE) -C init

.PHONY:clean
clean:
	-$(MAKE) -C init clean
	-$(MAKE) -C kernel clean