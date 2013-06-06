
CC = gcc
CFLAGS = -g -O -Wall
LDFLAGS = 


## DO NOT CHANGE ANYTHING BELOW THIS LINE #####################################

all test:  mmxtest ../libmmxemu.so
	LD_PRELOAD=../libmmxemu.so ./mmxtest > mmxtest_out 2> mmxtest_err
	cmp mmxtest_out mmxtest_err || diff mmxtest_out mmxtest_err

mmxtest: mmxtest.o
	$(CC) $(LDFLAGS) -o $@ $?

mmxtest.o: mmxtest.s
	$(CC) $(CFLAGS) -c -o $@ $?

mmxtest.s: mmxtest.c
	$(CC) $(CFLAGS) -S -o $@ $?

../libmmxemu.so:
	$(MAKE) -C ../src

clean:
	rm -f *.o mmxtest.s mmxtest mmxtest_out mmxtest_err core

