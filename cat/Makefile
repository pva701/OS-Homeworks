all: cat

cat: cat.c
	gcc cat.c -L../lib -I../lib -Wl,-rpath=../lib -lhelpers -o cat
clean:
	rm -f cat

