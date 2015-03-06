all: libhelpers.so

libhelpers.so: helpers.o
	gcc -shared -o libhelpers.so helpers.o

helpers.o: helpers.c
	gcc -fpic -c helpers.c

clean:
	rm -f *.o
	rm -f *.so
