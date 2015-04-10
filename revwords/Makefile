CC = gcc
CC_FLAGS = 

all: revwords

revwords: revwords.c
	$(CC) $(CC_FLAGS) revwords.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o revwords
clean:
	rm -f revwords

