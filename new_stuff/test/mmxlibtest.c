/*
 * This is the mmx-test programm from libmmx using libxmmemu library
 * adapted by Oliver Delise <delise@online-club.de>, June 1998
 */
 
 
#include <signal.h>
#include <stdio.h>
#include "mmx_types.h"
// #include "sigill_handler.h"

int main()
{
	int rval;
	mmx_t ma;
	mmx_t mb;
	rval = 1;
	/* Announce return value of mmx_ok() */
	printf(" *** Bogus message since we are emulating so MMX does allways exist ***\n");
	printf(" Value returned from init was %x.", rval);
	printf(" (Indicates MMX %s available)\n\n",(rval)? "is" : "not");
	fflush(stdout); fflush(stderr);
	if(rval) {
		/* PADD *****************************************************/
		ma.q = 0x1111111180000000LL;
		mb.q = 0x7fffffff00000001LL;
		paddd( &ma, &mb);
		fprintf(stdout, "paddd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddd: mb.q is 9111111080000001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x0001000100010001LL;
		mb.q = 0x80007fffffff0001LL;
		paddw( &ma, &mb);
		fprintf(stdout, "paddw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddw: mb.q is 8001800000000002\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010000LL;
		paddw( &ma, &mb);
		fprintf(stdout, "paddw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddw: mb.q is 8001800000000001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x01010101807fff01LL;
		mb.q = 0x807fff0101010101LL;
		paddb( &ma, &mb);
		fprintf(stdout, "paddb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddb: mb.q is 8180000281800002\n");
		fflush(stdout); fflush(stderr);


		/* PADDS ****************************************************/
		ma.q = 0x0001000100010001LL;
		mb.q = 0x80007fffffff0001LL;
		paddsw( &ma, &mb);
		fprintf(stdout, "paddsw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddsw: mb.q is 80017fff00000002\n");

		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010000LL;
		paddsw( &ma, &mb);
		fprintf(stdout, "paddsw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddsw: mb.q is 80017fff00000001\n");

		ma.q = 0x01010101807fff01LL;
		mb.q = 0x807fff0101010101LL;
		paddsb( &ma, &mb);
		fprintf(stdout, "paddsb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddsb: mb.q is 817f0002817f0002\n");
		fflush(stdout); fflush(stderr);


		/* PADDUS ***************************************************/
		ma.q = 0x0001000100010001LL;
		mb.q = 0x80007fffffff0001LL;
		paddusw( &ma, &mb);
		fprintf(stdout, "paddusw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddusw: mb.q is 80018000ffff0002\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010000LL;
		paddusw( &ma, &mb);
		fprintf(stdout, "paddusw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddusw: mb.q is 80018000ffff0001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x01010101807fff01LL;
		mb.q = 0x807fff0101010101LL;
		paddusb( &ma, &mb);
		fprintf(stdout, "paddusb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "paddusb: mb.q is 8180ff028180ff02\n");
		fflush(stdout); fflush(stderr);


		/* PSUB *****************************************************/
		ma.q = 0x7fffffff00000001LL;
		mb.q = 0x1111111180000000LL;
		psubd( &ma, &mb);
		fprintf(stdout, "psubd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubd: mb.q is 911111127fffffff\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010001LL;
		psubw( &ma, &mb);
		fprintf(stdout, "psubw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubw: mb.q is 8001800200020000\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x0001000100010000LL;
		mb.q = 0x80007fffffff0001LL;
		psubw( &ma, &mb);
		fprintf(stdout, "psubw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubw: mb.q is 7fff7ffefffe0001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x807fff0101010101LL;
		mb.q = 0x01010101807fff01LL;
		psubb( &ma, &mb);
		fprintf(stdout, "psubb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubb: mb.q is 818202007f7efe00\n");
		fflush(stdout); fflush(stderr);


		/* PSUBS ****************************************************/
		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010001LL;
		psubsw( &ma, &mb);
		fprintf(stdout, "psubsw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubsw: mb.q is 7fff800200020000\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x0001000100010000LL;
		mb.q = 0x80007fffffff0001LL;
		psubsw( &ma, &mb);
		fprintf(stdout, "psubsw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubsw: mb.q is 80007ffefffe0001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x807fff0101010101LL;
		mb.q = 0x01010101807fff01LL;
		psubsb( &ma, &mb);
		fprintf(stdout, "psubsb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubsb: mb.q is 7f820200807efe00\n");
		fflush(stdout); fflush(stderr);
 

		/* PSUBUS ***************************************************/
		ma.q = 0x80007fffffff0001LL;
		mb.q = 0x0001000100010001LL;
		psubusw( &ma, &mb);
		fprintf(stdout, "psubusw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubusw: mb.q is 0000000000000000\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x0001000100010000LL;
		mb.q = 0x80007fffffff0001LL;
		psubusw( &ma, &mb);
		fprintf(stdout, "psubusw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubusw: mb.q is 7fff7ffefffe0001\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x807fff0101010101LL;
		mb.q = 0x01010101807fff01LL;
		psubusb( &ma, &mb);
		fprintf(stdout, "psubusb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psubusb: mb.q is 000000007f7efe00\n");
		fflush(stdout); fflush(stderr);


		/* PMUL *****************************************************/
		ma.q = 0x8000ffff00ff0000LL;
		mb.q = 0x0200ffff00ffffffLL;
		pmulhw( &ma, &mb);
		fprintf(stdout, "pmulhw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pmulhw: mb.q is ff00000000000000\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0200ffff00ffffffLL;
		pmullw( &ma, &mb);
		fprintf(stdout, "pmullw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pmullw: mb.q is 00000001fe010000\n");
		fflush(stdout); fflush(stderr);


		/* PMADD ****************************************************/
		ma.q = 0x8000345680007f34LL;
		mb.q = 0x93234a27ffff1707LL;

		pmaddwd( &ma, &mb);
		fprintf(stdout, "pmaddwd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pmaddwd: mb.q is 4597551a0b71a66c\n");
		fflush(stdout); fflush(stderr);


		/* PCMPEQ ***************************************************/
		ma.q = 0x800034568f237f34LL;
		mb.q = 0x93009a568f237f34LL;

		pcmpeqd( &ma, &mb);
		fprintf(stdout, "pcmpeqd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpeqd: mb.q is 00000000ffffffff\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x93009a568f237f34LL;
		pcmpeqw( &ma, &mb);
		fprintf(stdout, "pcmpeqw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpeqw: mb.q is 00000000ffffffff\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x93009a568f237f34LL;
		pcmpeqb( &ma, &mb);
		fprintf(stdout, "pcmpeqb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpeqb: mb.q is 00ff00ffffffffff\n");
		fflush(stdout); fflush(stderr);



		/* PCMPGT ***************************************************/
		ma.q = 0x666688884477aaffLL;
		mb.q = 0x1234567890abcdefLL;

		pcmpgtd( &ma, &mb);
		fprintf(stdout, "pcmpgtd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpgtd: mb.q is 0000000000000000\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x1234567890abcdefLL;
		pcmpgtw( &ma, &mb);
		fprintf(stdout, "pcmpgtw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpgtw: mb.q is 0000ffff0000ffff\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x1234567890abcdefLL;
		pcmpgtb( &ma, &mb);
		fprintf(stdout, "pcmpgtb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pcmpgtb: mb.q is 0000ffff0000ff00\n");
		fflush(stdout); fflush(stderr);


		/* PACKSS ***************************************************/
		ma.q = 0x00012222000abbbbLL;
		mb.q = 0x0000888800003333LL;

		packssdw( &ma, &mb);
		fprintf(stdout, "packssdw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "packssdw: mb.q is 7fff7fff7fff3333\n");
		fflush(stdout); fflush(stderr);

		ma.q = 0x00aa00dd01009999LL;
		mb.q = 0x0011002200330044LL;

		packsswb( &ma, &mb);
		fprintf(stdout, "packsswb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "packsswb: mb.q is 7f7f7f8011223344\n");
		fflush(stdout); fflush(stderr);


		/* PACKUS ***************************************************/
		ma.q = 0x00aa00dd01009999LL;
		mb.q = 0x0011002200330044LL;

		packuswb( &ma, &mb);
		fprintf(stdout, "packuswb: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "packuswb: mb.q is aaddff0011223344\n");
		fflush(stdout); fflush(stderr);


		/* PUNPCKH **************************************************/
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;

		punpckhdq( &ma, &mb);
		fprintf(stdout, "punpckhdq: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpckhdq: mb.q is 090a0b0c01020304\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0102030405060708LL;
		punpckhwd( &ma, &mb);
		fprintf(stdout, "punpckhwd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpckhwd: mb.q is 090a01020b0c0304\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0102030405060708LL;
		punpckhbw( &ma, &mb);
		fprintf(stdout, "punpckhbw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpckhbw: mb.q is 09010a020b030c04\n");
		fflush(stdout); fflush(stderr);


		/* PUNPCKL **************************************************/
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;

		punpckldq( &ma, &mb);
		fprintf(stdout, "punpckldq: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpckldq: mb.q is 0d0e0f0005060708\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0102030405060708LL;
		punpcklwd( &ma, &mb);
		fprintf(stdout, "punpcklwd: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpcklwd: mb.q is 0d0e05060f000708\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0102030405060708LL;
		punpcklbw( &ma, &mb);
		fprintf(stdout, "punpcklbw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "punpcklbw: mb.q is 0d050e060f070008\n");
		fflush(stdout); fflush(stderr);



		/* PAND, PANDN, POR, PXOR ***********************************/
		ma.q = 0x5555555555555555LL;
		mb.q = 0x3333333333333333LL;

		pand( &ma, &mb);
		fprintf(stdout, "pand: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pand: mb.q is 1111111111111111\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x3333333333333333LL;
		pandn( &ma, &mb);
		fprintf(stdout, "pandn: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pandn: mb.q is 4444444444444444\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x3333333333333333LL;
		por( &ma, &mb);
		fprintf(stdout, "por: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "por: mb.q is 7777777777777777\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x3333333333333333LL;
		pxor( &ma, &mb);
		fprintf(stdout, "pxor: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pxor: mb.q is 6666666666666666\n");
		fflush(stdout); fflush(stderr);



		/* PSLL *****************************************************/
		ma.q = 0x0000000000000018LL;
		mb.q = 0x0123456789abcdefLL;

		psllq( &ma, &mb);
		fprintf(stdout, "psllq: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psllq: mb.q is 6789abcdef000000\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0123456789abcdefLL;
		pslld( &ma, &mb);
		fprintf(stdout, "pslld: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "pslld: mb.q is 67000000ef000000\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0123456789abcdefLL;
		psllw( &ma, &mb);
		fprintf(stdout, "psllw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psllw: mb.q is 0000000000000000\n");
		fflush(stdout); fflush(stderr);



		/* PSRL *****************************************************/
		ma.q = 0x0000000000000018LL;
		mb.q = 0x0123456789abcdefLL;

		psrlq( &ma, &mb);
		fprintf(stdout, "psrlq: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psrlq: mb.q is 0000000123456789\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0123456789abcdefLL;
		psrld( &ma, &mb);
		fprintf(stdout, "psrld: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psrld: mb.q is 0000000100000089\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0123456789abcdefLL;
		psrlw( &ma, &mb);
		fprintf(stdout, "psrlw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psrlw: mb.q is 0000000000000000\n");
		fflush(stdout); fflush(stderr);



		/* PSRA *****************************************************/
		ma.q = 0x0000000000000018LL;
		mb.q = 0x0123456789abcdefLL;

		psrad( &ma, &mb);
		fprintf(stdout, "psrad: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psrad: mb.q is 00000001ffffff89\n");
		fflush(stdout); fflush(stderr);

		mb.q = 0x0123456789abcdefLL;
		psraw( &ma, &mb);
		fprintf(stdout, "psraw: mb.q is %016llx\n", mb.q);
		fprintf(stderr, "psraw: mb.q is 00000000ffffffff\n");
		fflush(stdout); fflush(stderr);

		/* Exit MXX *************************************************/
		// emms();
	}

	/* Clean-up and exit nicely */
	exit(0);
}
