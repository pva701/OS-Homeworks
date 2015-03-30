CC = gcc

all: bufcat

bufcat: libbufio.so
	$(CC) bufcat.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o bufcat
libbufio.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f bufcat

