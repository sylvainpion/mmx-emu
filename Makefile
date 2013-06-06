#### Automagic Makefile ####

.PHONY: test

all:
	$(MAKE) -C src

test:
	$(MAKE) -C test

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	rm -f libmmxemu.so core
