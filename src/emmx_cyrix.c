/*
 * Emulation code of the Cyrix EMMX instruction set.
 * (C) <Vincent.Renardias@waw.com>, 1998, LGPL.
 */

#include "emu.h"
#include "context.h"
#include "saturate.h"
#include "mmx_arithmetic.h"

#define        ABS(a)  ( (a) > 0 ? (a) : (-a) )

void paveb (void *src, void *dest)
{
	// Note the comment in Cyrix' doc: "M2 hardware versions before v1.3
	// interpret values as signed bytes on this instruction".
	unsigned char *s = (char *) src;
	unsigned char *d = (char *) dest;
	int i;
	for (i=0; i<8; i++)
		d[i] = ((unsigned)d[i] + (unsigned)s[i]) >> 1;
	mmx_printf("paveb called\n");
}

void pdistib (void *src, void *dest)
{
	char *s = (char *) src;
	char *d = (char *) dest;
	char *impl = (char *) IMPL_REG(dest);
	int i;
	for (i=0; i<8; i++)
		impl[i]=saturatecharunsigned(	(int)impl[i] +
						ABS((int)d[i] - (int)s[i]) );
	mmx_printf("pdistib called\n"); 
}

void pmagw (void *src, void *dest) 
{ 
	short *s = (short *) src; 
	short *d = (short *) dest;
	int i;
	for(i=0;i<4;i++)
		if (ABS(d[i]) > ABS(s[i])) 
			d[i]=s[i];
	mmx_printf("pmagw called\n"); 
}

// pmulhrw conflicts with AMD's one, and have a different semantic !
// I call AMD's one pmulhrw_3dnow.

#define EMMX_MACRO_PM(NAME,OPER,DEST)		\
void NAME (void *src, void *dest)		\
{						\
	short *s = (short *) src;		\
	short *d = (short *) dest;		\
	short *impl __attribute__((__unused__)) = (short *) IMPL_REG(dest); \
	int i;					\
	for (i=0; i<4; i++)			\
		DEST[i] OPER ((int)d[i]*(int)s[i] + 0x00004000L) >> 17; \
	mmx_printf(#NAME " called\n");		\
}

EMMX_MACRO_PM(pmulhrw,   =, d)
EMMX_MACRO_PM(pmulhriw,  =, impl)
EMMX_MACRO_PM(pmachriw, +=, impl)


#define EMMX_MACRO(NAME, SYMB)			\
void NAME (void *src, void *dest)		\
{						\
	char *s = (char *) src;			\
	char *d = (char *) dest;		\
	char *impl = (char *) IMPL_REG(dest);	\
	int i;					\
	for (i=0; i<8; i++)			\
		if (impl[i] SYMB 0)		\
			d[i] = s[i];		\
	mmx_printf(#NAME " called\n");		\
}

EMMX_MACRO(pmvzb, ==)
EMMX_MACRO(pmvnzb, !=)
EMMX_MACRO(pmvlzb, <)
EMMX_MACRO(pmvgezb, >=)


#define EMMX_ARITH(NAME, NAME2)				\
void NAME (void *src, void *dest)			\
{							\
	long long *impl = (long long *) IMPL_REG(dest);	\
	*impl = * (long long *) dest;			\
	NAME2(src, impl);				\
	mmx_printf(#NAME " called\n");			\
}

EMMX_ARITH(paddsiw, paddsw)
EMMX_ARITH(psubsiw, psubsw)
