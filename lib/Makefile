CC = gcc
CC_FLAGS = 

all: libhelpers.so

libhelpers.so: helpers.o
	$(CC) $(CC_FLAGS) -shared -o libhelpers.so helpers.o

helpers.o: helpers.c
	$(CC) -fpic -c helpers.c $(CC_FLAGS)

clean:
	rm -f *.o
	rm -f *.so
