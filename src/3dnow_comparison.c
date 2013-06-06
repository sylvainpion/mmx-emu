/*
 * Emulation code of the 3DNow!(tm) comparison functions.
 * (C) Oliver Delise <delise@online-club.de>, 1998, LGPL
 */

#include "emu.h"

#define MMX_EMU_3dn_CMP_MACRO(NAME, SYMB)		\
void NAME (void *src, void *dest) {			\
	float *d = (float *) dest;			\
	float *s = (float *) src;			\
	int  *dd = (int *) dest;			\
							\
	dd[0] = (d[0] SYMB s[0]) ? -1 : 0;		\
	dd[1] = (d[1] SYMB s[1]) ? -1 : 0;		\
	mmx_printf(#NAME " called\n");			\
}

MMX_EMU_3dn_CMP_MACRO(pfcmpeq, ==)
MMX_EMU_3dn_CMP_MACRO(pfcmpge, >=)
MMX_EMU_3dn_CMP_MACRO(pfcmpgt, >)
