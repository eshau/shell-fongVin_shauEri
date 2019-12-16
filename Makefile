ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: shell.o commands.o aux.o
	$(CC) -o shell shell.o commands.o aux.o
	rm *.o

shell.o: shell.c commands.h aux.h
	$(CC) -c shell.c

commands.o: commands.c commands.h aux.h
	$(CC) -c commands.c

aux.o: aux.c aux.h commands.h
	$(CC) -c aux.c

run:
	./shell

memcheck:
	valgrind --leak-check=yes ./shell

clean:
	rm *.o
	rm *~
