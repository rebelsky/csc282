CFLAGS = -g -Wall

EXAMPLES = sq-array-00 

TESTS = sq-array-test-00

PROGRAMS = $(EXAMPLES) $(TESTS)

default: $(PROGRAMS) 

clean:
	rm -f *.o

distclean: clean
	rm -f $(PROGRAMS)

# +----------+-------------------------------------------------------
# | Examples |
# +----------+

sq-array-00: sq-array.o sq-example-00.o
	$(CC) -o $@ $^

# +-------+----------------------------------------------------------
# | Tests |
# +-------+

sq-array-test-00: sq-array.o sq-test-00.o
	$(CC) -o $@ $^

dtest: d-test.o sq-d.o
	$(CC) -o $@ $^
