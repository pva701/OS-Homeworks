CC = gcc

all: forking polling

forking: libbufio.so
	$(CC) forking.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o forking

polling: libbufio.so
	$(CC) -std=c11 polling.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o polling

libbufio.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f forking
	rm -f polling
