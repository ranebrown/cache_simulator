CC = clang
FLAGS =  -Wall -Wextra
CFLAGS = -c -g -Wall -Wextra

.PHONY: all clean

all: test.exe

test.exe: doubleLinkedList.o
	$(CC) $(FLAGS) $^ -o $@ testList.c

doubleLinkedList.o: doubleLinkedList.c doubleLinkedList.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f *.exe
