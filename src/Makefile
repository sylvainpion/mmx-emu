#### Automagic Makefile ####

CC = gcc
CFLAGS = -g -O2 -Wall -fpic -funroll-loops -fomit-frame-pointer
LDFLAGS = -shared -lm

#CFLAGS += -DMMX_DEBUG

###########################################

.c.o:
	$(CC) $(CFLAGS) -c $+

CFLAGS += -I../include

all:	libmmxemu.so

libmmxemu.so: \
	sigill_handler.o decode.o\
	mmx_arithmetic.o mmx_logical.o mmx_conversion.o mmx_comparison.o\
	mmx_emms.o mmx_moves.o mmx_shift.o\
	emmx_cyrix.o\
	3dnow_arithmetic.o 3dnow_comparison.o 3dnow_conversion.o 3dnow_init.o\
	3dnow_transcendental.o 3dnow_decode.o

	$(CC) $(LDFLAGS) -o $@ $+

clean:
	rm -f *.o libmmxemu.so core
