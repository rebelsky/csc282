# Default targets

CC = clang

CFLAGS = -g -Wall

APPS = gcd

LIBS = srmathlib.so

all: $(APPS) $(LIBS)

check: gcdtest
	./gcdtest

install: srmathlib.so
	install srmathlib.so /usr/local/lib

clean:
	rm -f *.o

distclean:
	rm -f *.o $(LIBS) gcdtest $(APPS)
	
# Executables
gcd: gcd.o srgcd.o
	$(CC) $(CFLAGS) $^ -o $@
gcdtest: srgcd.o gcdtest.o srtest.o 
	$(CC) $(CFLAGS) $^ -o $@

# Libraries
srmathlib.so: srgcd.o
	$(CC) $(CFLAGS) -shared srgcd.o -o srmathlib.so

# All those awesome .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
gcd.o: srmath.h
srgcd.o: srmath.h
srtest.o: srtest.h
gcdtest.o: srtest.h srmath.h

#gcd.o: gcd.c srmath.h
#	$(CC) $(CFLAGS) -c $< -o $@
#srgcd.o: srgcd.c srmath.h
#	$(CC) $(CFLAGS) -c $< -o $@
#srtest.o: srtest.c srtest.h 
#	$(CC) $(CFLAGS) -c $< -o $@
#gcdtest.o: gcdtest.c srmath.h srtest.h
#	$(CC) $(CFLAGS) -c $< -o $@
#
