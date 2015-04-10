CC = gcc
CC_FLAGS = 

all: revwords

revwords: libhelpers.so
	$(CC) $(CC_FLAGS) revwords.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o revwords
libhelpers.so: ../lib
	$(MAKE) -C $<
clean:
	rm -f revwords

