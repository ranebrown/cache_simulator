CC = clang
CFLAGS = -c -g -Wall -Wextra


.PHONY: all clean

all: cacheCodeTest

cacheCodeTest: cacheCodeTest.o cacheCode.o
	$(CC) $(LFLAGS) $^ -o $@

cacheCode.o: cacheCode.c cacheCode.h
	$(CC) $(CFLAGS) $<

cacheCodeTest.o: cacheCodeTest.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f cacheCodeTest
	rm -f *.o
