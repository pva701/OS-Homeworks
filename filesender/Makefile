CC = gcc

all: filesender

filesender: libbufio.so
	$(CC) filesender.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o filesender
libbufio.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f filesender

