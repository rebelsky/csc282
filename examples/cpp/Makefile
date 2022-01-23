
# If you are on windows, please uncomment the following line
# ARCH = -DWINDOWZ32

CFLAGS = -DDEBUG $(ARCH)

testfoo: foo.o testfoo.o
	cc $^ -o $@
