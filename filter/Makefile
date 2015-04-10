CC = gcc

all: filter

filter: filter.c
	$(CC) filter.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o filter 
clean:
	rm -f filter

