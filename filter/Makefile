CC = gcc

all: filter

filter: libhelpers.so
	$(CC) filter.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o filter 
libhelpers.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f filter

