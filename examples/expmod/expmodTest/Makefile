# Default targets

CC = clang

CFLAGS = -g -Wall

APPS = expmodTest

all: $(APPS) $(LIBS)

check: expmodTest
	./expmodTest

clean:
	rm -f *.o

distclean:
	rm -f *.o $(LIBS) gcdtest $(APPS)
	
# Executables
expmod: expmod.o
	$(CC) $(CFLAGS) $^ -o $@
expmodTest: expmod.o expmodTest.o srtest.o 
	$(CC) $(CFLAGS) $^ -o $@

# Libraries
#srmathlib.so: srgcd.o
#	$(CC) $(CFLAGS) -shared srgcd.o -o srmathlib.so

# All those awesome .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
srtest.o: srtest.h
expmodTest.o: srtest.h

#gcd.o: gcd.c srmath.h
#	$(CC) $(CFLAGS) -c $< -o $@
#srgcd.o: srgcd.c srmath.h
#	$(CC) $(CFLAGS) -c $< -o $@
#srtest.o: srtest.c srtest.h 
#	$(CC) $(CFLAGS) -c $< -o $@
#gcdtest.o: gcdtest.c srmath.h srtest.h
#	$(CC) $(CFLAGS) -c $< -o $@
#