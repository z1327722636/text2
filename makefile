CC = gcc
target = 3301_mysh
src = $(wildcard *.c)
objects = $(patsubst %.c,%.o,$(src))
$(target):$(objects)
	$(CC) -std=c99 -o $(target) $(objects)
%.o:%.c
	$(CC) -std=c99 -c $<

.PHONY:clean
clean:
	rm $(target) $(objects)






