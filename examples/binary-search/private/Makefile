
CC = clang

CFLAGS = -g -Wall

MORE_CFLAGS = -L. -lbs

default: bsi-expt bsi-tests

bs.o: bs.c bs.h
	$(CC) $(CFLAGS) -o $@ -c $<

libbs.so: bs.o
	$(CC) -shared -o $@ $^

bsi-expt: bsi-expt.o libbs.so
	$(CC) $(CLAGS) $(MORE_CFLAGS) -o $@ $<

bsi-tests: bsi-tests.o libbs.so
	$(CC) $(CLAGS) $(MORE_CFLAGS) -o $@ $<
