all:head.o mtrap.o entry.o start.o strap.o csr.o
head.o:head.S
	$(AS) $(ASFLAGS) -o $@ $< 
entry.o:entry.S
	$(AS) $(ASFLAGS) -o $@ $< 
switch.o:switch.S
	$(AS) $(ASFLAGS) -o $@ $< 

.PHONY:clean
clean:
	-rm -f *.o
