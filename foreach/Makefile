CC = gcc

all: foreach

foreach: foreach.c
	$(CC) foreach.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -lhelpers -o foreach
clean:
	rm -f foreach

