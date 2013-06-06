/*
 * Emulation code of the comparison functions.
 * Copyright  Sylvain Pion, July 1998.
 */

#include "emu.h"

#define MMX_EMU_CMP_MACRO(NAME, TYPE, LOOP, SYMB)	\
void NAME (void *src, void *dest) {			\
	int i;						\
        TYPE *d = (TYPE *) dest;			\
        TYPE *s = (TYPE *) src;			\
	for (i=0; i < LOOP; i++)			\
		d[i] = (d[i] SYMB s[i]) ? -1 : 0;	\
        mmx_printf(#NAME " called\n");			\
}

MMX_EMU_CMP_MACRO(pcmpeqb, char,  8, ==)
MMX_EMU_CMP_MACRO(pcmpeqw, short, 4, ==)
MMX_EMU_CMP_MACRO(pcmpeqd, int,   2, ==)

MMX_EMU_CMP_MACRO(pcmpgtb, char,  8, >)
MMX_EMU_CMP_MACRO(pcmpgtw, short, 4, >)
MMX_EMU_CMP_MACRO(pcmpgtd, int,   2, >)
