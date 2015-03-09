CC = gcc

all: cat

cat: libhelpers.so
	$(CC) cat.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o cat
libhelpers.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f cat

