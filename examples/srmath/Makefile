# SRMath's not-so-amazing Makefile

# gcd.c gcdtest.c Makefile srgcd.c srmath.h srtest.c srtest.h testdemo.c

default: executables library

clean:
	rm -f *.o

distclean: clean
	rm -f libsrmath.so gcd gcdtest

# +---------+--------------------------------------------------------
# | Library |
# +---------+

library: srmath.so

srmath.so: srgcd.o
	cc srgcd.o -shared -o libsrmath.so

# +-------------+----------------------------------------------------
# | Executables |
# +-------------+

executables: gcdtest gcd

gcdtest: gcdtest.o srgcd.o srtest.o
	cc gcdtest.o srgcd.o srtest.o -o gcdtest

gcd: gcd.o srgcd.o
	cc gcd.o srgcd.o -o gcd

# +--------------+---------------------------------------------------
# | Object Files |
# +--------------+

gcd.o: gcd.c srmath.h
	cc -c gcd.c -o gcd.o	

srgcd.o: srgcd.c srmath.h
	cc -c srgcd.c -o srgcd.o	

gcdtest.o: gcdtest.c srmath.h srtest.h
	cc -c gcdtest.c -o gcdtest.o	

srtest.o: srtest.c srtest.h
	cc -c srtest.c -o srtest.o
