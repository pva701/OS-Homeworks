CC = gcc

all: forking

forking: libbufio.so
	$(CC) forking.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o forking
libbufio.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f forking
