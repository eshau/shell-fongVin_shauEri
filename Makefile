ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: shell.o
	$(CC) -o shell shell.o

shell.o: shell.c
	$(CC) -c shell.c

run:
	./shell

memcheck:
	valgrind --leak-check=yes ./shell

clean:
	rm *.o
	rm *~
