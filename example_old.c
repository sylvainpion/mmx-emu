#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../libmmx-980616/mmx.h"

int main (void)
{
	mmx a, b, c, d, e;

	if (SIG_ERR == signal(SIGILL, mmx_ill_handler))
		printf("SIG_ILL handler not installed sucessfully.\n");

	if ( !mmx_init() ) {
		printf ( "MMX not supported\n" );
		exit;
	}

{
register unsigned int pipo asm("esi") = 0x07777777;
	/* Arithmetic */
	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_paddd( a, b );
	d = mmx_paddw( a, b );
	e = mmx_paddb( a, b );
}
	printf ( "padd:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	d = mmx_paddsw( a, b );
	e = mmx_paddsb( a, b );
	printf ( "padds:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	d = mmx_paddusw( a, b );
	e = mmx_paddusb( a, b );
	printf ( "paddus:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_pmaddwd( a, b );
	printf ( "pmadd:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	d = mmx_pmulhw( a, b );
	e = mmx_pmullw( a, b );
	printf ( "pmul:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_psubd( a, b );
	d = mmx_psubw( a, b );
	e = mmx_psubb( a, b );
	printf ( "psub:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	d = mmx_psubsw( a, b );
	e = mmx_psubsb( a, b );
	printf ( "psubs:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	d = mmx_psubusw( a, b );
	e = mmx_psubusb( a, b );
	printf ( "psubus:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );


	/* Comparisons */
	a = 0xaaccee00aaccee00LL;
	b = 0xaaaaee00aaccee00LL;
	c = mmx_pcmpeqd( a, b );
	d = mmx_pcmpeqw( a, b );
	e = mmx_pcmpeqb( a, b );
	printf ( "pcmpeq:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0xaaccee00abcdef01LL;
	b = 0xaaaaee00aaccee00LL;
	c = mmx_pcmpgtd( a, b );
	d = mmx_pcmpgtw( a, b );
	e = mmx_pcmpgtb( a, b );
	printf ( "pcmpgt:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	/* Conversion */
	a = 0x0123456789abcdefLL;
	b = 0xfedcba9876543210LL;
	c = mmx_packssdw( a, b );
	d = mmx_packsswb( a, b );
	printf ( "packss:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );

	a = 0x0123456789abcdefLL;
	b = 0xfedcba9876543210LL;
	c = mmx_packuswb( a, b );
	printf ( "packus:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	a = 0x0123456789abcdefLL;
	b = 0xfedcba9876543210LL;
	c = mmx_punpckhdq( a, b );
	d = mmx_punpckhwd( a, b );
	e = mmx_punpckhbw( a, b );
	printf ( "punpckh:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 0xfedcba9876543210LL;
	c = mmx_punpckldq( a, b );
	d = mmx_punpcklwd( a, b );
	e = mmx_punpcklbw( a, b );
	printf ( "punpckl:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	/* Logical */
	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_pand( a, b );
	printf ( "pand:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_pandn( a, b );
	printf ( "pandn:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_por( a, b );
	printf ( "por:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	a = 0x0123456789abcdefLL;
	b = 0xaaaaaaaaaaaaaaaaLL;
	c = mmx_pxor( a, b );
	printf ( "pxor:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );

	/* Shift */
	a = 0x0123456789abcdefLL;
	b = 4;
	c = mmx_psllq( a, b );
	d = mmx_pslld( a, b );
	e = mmx_psllw( a, b );
	printf ( "psll:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 4;
	d = mmx_psrad( a, b );
	e = mmx_psraw( a, b );
	printf ( "psra:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	a = 0x0123456789abcdefLL;
	b = 4;
	c = mmx_psrlq( a, b );
	d = mmx_psrld( a, b );
	e = mmx_psrlw( a, b );
	printf ( "psrl:\n" );
	printf ( "a is %016llx\n", (long long)a );
	printf ( "b is %016llx\n", (long long)b );
	printf ( "c is %016llx\n", (long long)c );
	printf ( "d is %016llx\n", (long long)d );
	printf ( "e is %016llx\n", (long long)e );

	mmx_exit();
	return 0;
}

