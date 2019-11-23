all:std.a

std.a:
	@$(MAKE) --no-print-directory -C drivers
	$(CC) $(CFLAGS) -c stdio.c -o stdio.o
	$(AR) cq std.a stdio.o drivers/ns16550a.o
.PHONY:clean
clean:
	@$(MAKE) --no-print-directory -C drivers clean
	-rm -f stdio.o std.a