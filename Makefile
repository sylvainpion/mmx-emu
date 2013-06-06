#### Automagic Makefile ####

.PHONY: test

CC=egcc

all:
	$(MAKE) -C src
	rm -f libmmxemu.so
	cp src/libmmxemu.so .
#	strip libmmxemu.so

test:
	$(MAKE) -C test

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	rm -f libmmxemu.so core
