CC = gcc

all: foreach

foreach: libbufio.so libhelpers.so
	$(CC) foreach.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -lhelpers -o foreach
libbufio.so: ../lib
	$(MAKE) -C $<
libhelpers.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f foreach

