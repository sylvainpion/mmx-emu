#### Automagic Makefile ####

CC = gcc
CFLAGS = -g -O -Wall -fpic -funroll-loops
LDFLAGS = -shared

# CFLAGS += -DMMX_DEBUG

###########################################

CFLAGS += -I../include

all:	libmmxemu.so
	rm -f ../libmmxemu.so
	cp libmmxemu.so ..

libmmxemu.so: mmx_ill_handler.o mmx_emu.o mmx_arithmetic.o mmx_shift.o mmx_logical.o mmx_conversion.o mmx_comparison.o
	$(CC) $(LDFLAGS) -o $@ $?

clean:
	rm -f *.o libmmxemu.so core
