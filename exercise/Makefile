src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall	-lm 

all:$(obj)
$(obj):%:%.c
	$(CC) $(CFLAGS) $< -o  $@
	
.PHONY:clean
clean:
	rm -rf $(obj)
