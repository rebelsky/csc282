CFLAGS=-g -Wall -O3
NOTICE = This is a notice

default: gcd

test: gcdtest
	./gcdtest

gcdtest: gcdtest.o srtest.o srmath.o
	cc -o gcdtest gcdtest.o srtest.o srmath.o

gcd.o: srmath.h
srmath.o: srmath.h

gcd: gcd.o srmath.o
	cc -o gcd gcd.o srmath.o

testdemo: testdemo.o srtest.o 
	cc -o testdemo testdemo.o srtest.o 

clean:
	rm -f *.o

distclean: clean
	rm -rf gcd gcdtest testdemo

shout:
	echo $(NOTICE)
        
