/*
 * Emulation code of the logical functions.
 * Copyright  Sylvain Pion, July 1998.
 */

#include "mmx_emu.h"

#define MMX_EMU_LOG_MACRO(NAME, SYMB)	    	\
void NAME (void *src, void *dest) {         	\
        int *d = (int *) dest;              	\
        int *s = (int *) src;               	\
	int i=0;				\
        d[i] = SYMB s[i];			\
	i=1;					\
        d[i] = SYMB s[i];			\
        mmx_printf(#NAME " called\n");          \
}

MMX_EMU_LOG_MACRO(pand, d[i] &);
MMX_EMU_LOG_MACRO(por,  d[i] |);
MMX_EMU_LOG_MACRO(pxor, d[i] ^);
MMX_EMU_LOG_MACRO(pandn, (d[i] ^ -1) &);

#if 0

/*
 * Note: The boolean operations don't seem to work with long longs. Pitty !
 * (at least with gcc-2.7.2.1 and gas-2.8.0.3)
 * Is this an alignment problem ?  A simple test program works...
 */

#define MMX_EMU_LOG_MACRO(NAME, SYMB)                   \
void NAME (void *src, void *dest) {                     \
        long long d = * (long long *) dest;             \
        long long s = * (long long *) src;              \
        d = SYMB s;                                     \
        mmx_printf(#NAME " called\n");                  \
}

MMX_EMU_LOG_MACRO(pand, d &);
MMX_EMU_LOG_MACRO(por,  d |);
MMX_EMU_LOG_MACRO(pxor, d ^);
MMX_EMU_LOG_MACRO(pandn, (d ^ (long long)-1) &);

#endif
