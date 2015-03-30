CC = gcc
CC_FLAGS = 

all: libhelpers.so libbufio.so

libhelpers.so: helpers.o
	$(CC) $(CC_FLAGS) -shared -o libhelpers.so helpers.o

helpers.o: helpers.c helpers.h
	$(CC) -fpic -c helpers.c $(CC_FLAGS)

bufio.o: bufio.c bufio.h
	$(CC) -fpic -c bufio.c $(CC_FLAGS)

libbufio.so: bufio.o
	$(CC) $(CC_FLAGS) -shared -o libbufio.so bufio.o

clean:
	rm -f *.o
	rm -f *.so
