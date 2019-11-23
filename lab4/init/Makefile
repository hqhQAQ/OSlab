all: main.o
%.o:%.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	-rm -f main.o