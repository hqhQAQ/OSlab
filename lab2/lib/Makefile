all:stdio

std.a:
	$(MAKE) -C drivers
	$(CC) $(CFLAGS) -o $@ $<
	$(AR) cq std.a stdio.o drivers/ns16550a.o