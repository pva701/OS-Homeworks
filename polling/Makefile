CC = gcc
CC_FLAGS = -std=c11
all: polling

polling: libbufio.so
	$(CC) $(CC_FLAGS) polling.c -L../lib -I../lib -Wl,-rpath=../lib -lbufio -o polling
libbufio.so: ../lib
	$(MAKE) -C $<
clean:
	$(MAKE) -C ../lib clean
	rm -f polling
