CC = gcc

all: bufcat

bufcat: bufcat.c
	$(CC) bufcat.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o bufcat
clean:
	$(MAKE) -C ../lib clean
	rm -f bufcat

