/*
 * Emulation code of the 3DNow!(tm) conversion functions.
 * (C) Oliver Delise <delise@online-club.de>, 1998, LGPL
 */

#include "emu.h"

#define MMX_EMU_3dn_CON_MACRO(NAME, STYPE, DTYPE)	\
void NAME (void *src, void *dest) {			\
	DTYPE *d = (DTYPE *) dest;			\
	STYPE *s = (STYPE *) src;			\
							\
	d[0] = (DTYPE) s[0];				\
	d[1] = (DTYPE) s[1];				\
	mmx_printf(#NAME " called\n");			\
}

// NB [syl]: does the C cast do exactly what is expected ?

MMX_EMU_3dn_CON_MACRO(pi2fd,   int, float)
MMX_EMU_3dn_CON_MACRO(pf2id, float,   int)
