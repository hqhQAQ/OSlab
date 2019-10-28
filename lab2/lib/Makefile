all:std.a

std.a:
	$(MAKE) -C drivers
	$(CC) $(CFLAGS) -o stdio.o stdio.c
	$(AR) cq std.a stdio.o drivers/ns16550a.o
.PHONY:clean
clean:
	$(MAKE) -C drivers clean
	rm -f stdio.o std.a