CC = gcc

all: libhelpers.so

libhelpers.so: helpers.o
	$(CC) -shared -o libhelpers.so helpers.o

helpers.o: helpers.c
	$(CC) -fpic -c helpers.c

clean:
	rm -f *.o
	rm -f *.so
