CC = gcc

all: filter

filter: filter.c
	$(CC) filter.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o filter 
clean:
	$(MAKE) -C ../lib clean
	rm -f filter

