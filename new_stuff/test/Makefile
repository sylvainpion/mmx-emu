#### Automagic Makefile ####

CC = gcc
#CFLAGS = -g -O -Wall
CFLAGS =  -I../../include -g -O -Wall -DMMX_DEBUG #-funroll-loops
LDFLAGS =
TESTPROG_LDFLAGS = -L../../ -lmmxemu -lm
SRC = ../../src/
LIBDIR = ./
TESTDIR = ./
AR = ar rc
RUNLIB = runlib
OBJS=		$(SRC)sigill_handler.o $(SRC)decode.o\
		$(SRC)mmx_emms.o $(SRC)mmx_moves.o $(SRC)mmx_arithmetic.o\
		$(SRC)mmx_shift.o $(SRC)mmx_logical.o $(SRC)mmx_conversion.o\
		$(SRC)mmx_comparison.o $(SRC)emmx_cyrix.o\
		$(SRC)3dnow_arithmetic.o $(SRC)3dnow_conversion.o\
		$(SRC)3dnow_comparison.o $(SRC)3dnow_init.o\
		$(SRC)3dnow_transcendental.o
		
###########################################

all:	libmmx_emu.a mmxlibtest mmx_v1 mmx_3dn cpuspeed libmmx_emu.so move_shared

libmmx_emu.a: 	$(OBJS)
		$(AR) $@ $(OBJS)
		-@ ($(RUNLIB) $@ || true) 2>/dev/null
		cp -f ./*.a ./lib/

libmmx_emu.so:  $(SRC)mmx_ill_handler.o $(SRC)mmx_decode.o\
		$(SRC)mmx_emms.o $(SRC)mmx_moves.o $(SRC)mmx_arithmetic.o\
		$(SRC)mmx_arithmetic.o $(SRC)mmx_shift.o $(SRC)mmx_logical.o\
		$(SRC)mmx_conversion.o $(SRC)mmx_comparison.o\
		$(SRC)mmx_cyrix.o\
		$(SRC)mmx_3dn_arithmetic.o $(SRC)mmx_3dn_conversion.o\
		$(SRC)mmx_3dn_comparison.o $(SRC)mmx_3dn_init.o
		$(CC) $(LDFLAGS) -shared -o $(LIBDIR)$@ $?

move_shared:
	mv -f ./*.so ./lib/


cpuspeed:
	$(CC) -o cpuspeed cpuspeed.c


mmx_v1: mmx_v1.o
	$(CC) -o $(TESTDIR)$@ $(TESTDIR)$? $(TESTPROG_LDFLAGS)

mmx_v1.s: $(TESTDIR)mmx_v1.c
	$(CC) $(CFLAGS) -S -o $(TESTDIR)$@ $?

mmx_v1.o: mmx_v1.s
	$(CC) $(CFLAGS) -c -o $(TESTDIR)$@ $(TESTDIR)$?

mmx_v2: mmx_v2.o
	$(CC) -o $(TESTDIR)$@ $(TESTDIR)$? $(TESTPROG_LDFLAGS)

mmx_v2.s: $(TESTDIR)mmx_v2.c
	$(CC) $(CFLAGS) -S -o $(TESTDIR)$@ $?

mmx_v2.o: mmx_v2.s
	$(CC) $(CFLAGS) -c -o $(TESTDIR)$@ $(TESTDIR)$?

mmx_3dn: mmx_3dn.o
	$(CC) -o $(TESTDIR)$@ $(TESTDIR)$? $(TESTPROG_LDFLAGS)

mmx_3dn.s: $(TESTDIR)mmx_3dn.c
	$(CC) $(CFLAGS) -S -o $(TESTDIR)$@ $?

mmx_3dn.o: mmx_3dn.s
	$(CC) $(CFLAGS) -c -o $(TESTDIR)$@ $(TESTDIR)$?

mmxlibtest: mmxlibtest.o
	$(CC) -o $(TESTDIR)$@ $(TESTDIR)$? $(TESTPROG_LDFLAGS)

mmxlibtest.s: $(TESTDIR)mmxlibtest.c
	$(CC) $(CFLAGS) -S -o $(TESTDIR)$@ $?

mmxlibtest.o: mmxlibtest.s
	$(CC) $(CFLAGS) -c -o $(TESTDIR)$@ $(TESTDIR)$?

#realclean: 
clean:
	rm -f $(SRC)*.o *.o $(LIBDIR)libmmx_emu.so $(TESTDIR)mmxlibtest.s \
        mmxlibtest.s mmxlibtest *.a *.so ./lib/*.a ./lib/*.so\
        mmx_v?.s mmx_v? mmx_3dn mmx_3dn.s *~ core cpuspeed

#clean: 
# rm -f $(LIBDIR)libmmx_emu.so
