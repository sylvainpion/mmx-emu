#### Automagic Makefile ####

CC = gcc
CFLAGS = -g -O -Wall
# CFLAGS = -g -O -Wall -DMMX_DEBUG
LDFLAGS = 

###########################################

all:	mmxtest libmmxemu.so

libmmxemu.so: mmx_ill_handler.o mmx_emu.o mmx_arithmetic.o mmx_shift.o mmx_logical.o mmx_conversion.o mmx_comparison.o
	$(CC) $(LDFLAGS) -shared -o $@ $?

mmxtest: mmxtest.o
	$(CC) $(LDFLAGS) -o $@ $?

mmxtest.s: mmxtest.c
	$(CC) $(CFLAGS) -S -o $@ $?

mmxtest.o: mmxtest.s
	$(CC) $(CFLAGS) -c -o $@ $?

clean:
	rm -f *.o libmmxemu.so mmxtest.s mmxtest core
