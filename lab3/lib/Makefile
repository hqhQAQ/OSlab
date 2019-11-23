all:std.a

std.a:drivers stdio.o
	@echo AR std.a
	@$(AR) cq std.a stdio.o drivers/ns16550a.o
	
%.o:%.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:drivers
drivers:
	@$(MAKE) --no-print-directory -C drivers

.PHONY:clean
clean:
	@$(MAKE) --no-print-directory -C drivers clean
	-rm -f stdio.o std.a