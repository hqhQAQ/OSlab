all:head.o mtrap.o entry.o start.o strap.o csr.o switch.o sched.o syscall.o
head.o:head.S
	@echo AS $@
	@$(AS) $(ASFLAGS) -o $@ $< 
entry.o:entry.S
	@echo AS $@
	@$(AS) $(ASFLAGS) -o $@ $< 
switch.o:switch.S
	@echo AS $@
	@$(AS) $(ASFLAGS) -o $@ $< 
%.o:%.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	-rm -f *.o
