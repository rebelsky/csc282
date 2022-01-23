# CFLAGS = -g -Wall -DLOGMATH
CFLAGS = -O3

default: emr

emr: em.o expmod-recursive.o logmath.o
	$(CC) -o $@ $^

ems: em.o expmod-slow.o logmath.o
	$(CC) -o $@ $^

emb: em.o expmod-bad.o logmath.o
	$(CC) -o $@ $^

emi: em.o expmod-iterative.o logmath.o
	$(CC) -o $@ $^

emn: em.o expmod-new.o logmath.o
	$(CC) -o $@ $^

emt: em.o expmod-tail.o logmath.o
	$(CC) -o $@ $^

emr-test: emtest.o srtest.o expmod-recursive.o logmath.o
	$(CC) -o $@ $^

ems-test: emtest.o srtest.o expmod-slow.o logmath.o
	$(CC) -o $@ $^

emb-test: emtest.o srtest.o expmod-bad.o logmath.o
	$(CC) -o $@ $^

emi-test: emtest.o srtest.o expmod-iterative.o logmath.o
	$(CC) -o $@ $^

emn-test: emtest.o srtest.o expmod-new.o logmath.o
	$(CC) -o $@ $^

emt-test: emtest.o srtest.o expmod-tail.o logmath.o
	$(CC) -o $@ $^

emr-time: time-expmod.o expmod-recursive.o logmath.o
	$(CC) -o $@ $^

emi-time: time-expmod.o expmod-iterative.o logmath.o
	$(CC) -o $@ $^

emn-time: time-expmod.o expmod-new.o logmath.o
	$(CC) -o $@ $^

ems-time: time-expmod.o expmod-slow.o logmath.o
	$(CC) -o $@ $^

emt-time: time-expmod.o expmod-tail.o logmath.o
	$(CC) -o $@ $^

emr-time2: time2-expmod.o expmod-recursive.o logmath.o
	$(CC) -o $@ $^

ems-time2: time2-expmod.o expmod-slow.o logmath.o
	$(CC) -o $@ $^

emt-time2: time2-expmod.o expmod-tail.o logmath.o
	$(CC) -o $@ $^
