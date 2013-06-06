/*
 * Emulation of the move functions.
 * Copyright  Sylvain Pion, 1998.
 */

#include "emu.h"
#include "context.h"

#define MMX_EMU_MOVES_2MEM_MACRO(NAME, TYPE)	\
void NAME (void *src, void *dest) {             \
        TYPE *s = (TYPE *) src;			\
        TYPE *d = (TYPE *) dest;		\
	*s = *d;				\
        mmx_printf(#NAME " called\n");		\
}

MMX_EMU_MOVES_2MEM_MACRO(movq2mem, long long);
MMX_EMU_MOVES_2MEM_MACRO(movd2mem, int);


#define MMX_EMU_MOVES_2MMX_MACRO(NAME, D_2)		\
void NAME (void *src, void *dest)			\
{							\
        int *d = (int *) dest;				\
        int *s = (int *) src;				\
	d[0] = s[0];					\
	d[1] = D_2;					\
	((struct _fpreg *) d)->exponent = 0xffff;	\
        mmx_printf(#NAME " called\n");			\
}

MMX_EMU_MOVES_2MMX_MACRO(movq2mmx, s[1]);
MMX_EMU_MOVES_2MMX_MACRO(movd2mmx, 0);
