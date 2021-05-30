CFLAGS = -g -Wall
CC = /usr/bin/gcc

default: gcd

gcd: test gcd.o srmath.o 
	$(CC) $(CFLAGS) -o gcd gcd.o srmath.o
gcd.o: gcd.c
	$(CC) $(CFLAGS) -c -o gcd.o gcd.c
srmath.o: srmath.c
	$(CC) $(CFLAGS) -c -o srmath.o srmath.c

clean:
	rm -f *.o gcd gcdtest

gcdtest: gcdtest.o srmath.o srtest.o
	$(CC) $(CFLAGS) -o $@ $^

test: gcdtest
	gcdtest

