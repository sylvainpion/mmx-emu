/*
 * Emulation code of the shift functions.
 * Copyright  Sylvain Pion, July 1998.
 */

#include "emu.h"

#define MMX_EMU_SHIFT_MACRO(NAME, TYPE, LOOP, SYMB)	\
void NAME (void *src, void *dest) {			\
        int i;						\
        TYPE *d = (TYPE *) dest;			\
        unsigned long s = * (unsigned long *) src;      \
        if (LOOP == 1 && s >= 64) s = 64;               \
        if (LOOP == 2 && s >= 32) s = 32;               \
        if (LOOP == 4 && s >= 16) s = 16;               \
        for (i=0; i < LOOP; i++)                        \
                if (s > 0) d[i]=(d[i] SYMB s-1) SYMB 1; \
        mmx_printf(#NAME " called\n");			\
}

MMX_EMU_SHIFT_MACRO(psllw, short, 4, <<);
MMX_EMU_SHIFT_MACRO(pslld, int,   2, <<);
MMX_EMU_SHIFT_MACRO(psllq, long long, 1, <<);

MMX_EMU_SHIFT_MACRO(psraw, signed short, 4, >>);
MMX_EMU_SHIFT_MACRO(psrad, signed int,   2, >>);

MMX_EMU_SHIFT_MACRO(psrlw, unsigned short, 4, >>);
MMX_EMU_SHIFT_MACRO(psrld, unsigned int,   2, >>);
MMX_EMU_SHIFT_MACRO(psrlq, unsigned long long, 1, >>);

extern int pshi_diff;

void pshimw(void *src, void *dest) {
	switch (pshi_diff) {
	case 2: psrlw(src,dest); break;
	case 4: psraw(src,dest); break;
	case 6: psllw(src,dest); break;
	};
	mmx_printf("pshimw function called\n");
}


void pshimd(void *src, void *dest) {
	switch (pshi_diff) {
	case 2: psrld(src,dest); break;
	case 4: psrad(src,dest); break;
	case 6: pslld(src,dest); break;
	};
	mmx_printf("pshimd function called\n");
}

void pshimq(void *src, void *dest) {
	switch (pshi_diff) {
	case 2: psrlq(src,dest); break;
//	case 4: psraq(src,dest); break;	// Doesn't exist.
	case 6: psllq(src,dest); break;
	};
	mmx_printf("pshimq function called\n");
}
