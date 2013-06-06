/*
 * Emulation code of the logical functions.
 * Copyright  Sylvain Pion, July 1998.
 */

#include "emu.h"

#define MMX_EMU_LOG_MACRO(NAME, SYMB)		\
void NAME (void *src, void *dest) {		\
        long long *d = (long long *) dest;	\
        long long *s = (long long *) src;	\
        *d = SYMB *s;				\
        mmx_printf(#NAME " called\n");		\
}

MMX_EMU_LOG_MACRO(pand, *d &);
MMX_EMU_LOG_MACRO(por,  *d |);
MMX_EMU_LOG_MACRO(pxor, *d ^);
MMX_EMU_LOG_MACRO(pandn, (*d ^ (long long)-1) &);
