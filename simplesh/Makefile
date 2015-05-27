CC = gcc

all: simplesh

simplesh: libhelpers.so libbufio.so
	$(CC) simplesh.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -lbufio -o simplesh
libhelpers.so: ../lib
	$(MAKE) -C $<

libbufio.so: ../lib
	$(MAKE) -C $<

clean:
	$(MAKE) -C ../lib clean
	rm -f simplesh
