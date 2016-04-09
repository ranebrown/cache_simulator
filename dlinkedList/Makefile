CC = clang
FLAGS =  -Wall -Wextra
CFLAGS = -c -g -Wall -Wextra

.PHONY: all clean

all: test.exe

test.exe: dlinkedList.o
	$(CC) $(FLAGS) $^ -o $@ testList.c

dlinkedList.o: dlinkedList.c dlinkedList.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f *.exe
	rm -rf *.dSYM
	rm -f *~
