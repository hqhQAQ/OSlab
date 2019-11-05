all:ns16550a.o
%.o:%.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f *.o