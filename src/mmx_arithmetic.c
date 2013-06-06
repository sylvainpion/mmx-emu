/*
 * Emulation code of the arithmetic functions.
 * (C) <Vincent.Renardias@waw.com>, 1998, LGPL.
 */

#include "mmx_emu.h"

#define saturatenone(a)	(a)

#define SATURATE(TYPE, SIGN, VALUE_MAX, VALUE_MIN)			\
static inline TYPE saturate##TYPE##SIGN (int a)				\
{									\
	if (a>(int)(SIGN TYPE)VALUE_MAX) return (TYPE) VALUE_MAX;	\
	if (a<(int)(SIGN TYPE)VALUE_MIN) return (TYPE) VALUE_MIN;	\
	return (TYPE) a;						\
}

SATURATE(char,    signed, 0x7F,   0x80)
SATURATE(char,  unsigned, 0xFF,   0x0)
SATURATE(short,   signed, 0x7FFF, 0x8000)
SATURATE(short, unsigned, 0xFFFF, 0x0)

/* Fake saturations for PMUL* instructions */

static inline short saturatelow  (int a)   { return (short) (a&0x0000FFFF); }
static inline short saturatehigh (int a)   { return (short) (a>>16); }


#define MMX_EMU_P_MACRO(NAME, TYPE, LOOP, SYMB, SATURATION)      \
void NAME (void *src, void *dest)                                \
{                                                                \
        int i;                                                   \
        TYPE *d = (TYPE *) dest;                                 \
        TYPE *s = (TYPE *) src;                                  \
        for (i=0; i < LOOP; i++)                                 \
		d[i] = saturate##SATURATION((int) d[i] SYMB (int) s[i]); \
        mmx_printf(#NAME " called\n");                           \
}

MMX_EMU_P_MACRO(paddb, char, 8, +, none)
MMX_EMU_P_MACRO(paddw, short, 4, +, none)
MMX_EMU_P_MACRO(paddd, int, 2, +, none)
MMX_EMU_P_MACRO(psubb, char, 8, -, none)
MMX_EMU_P_MACRO(psubw, short, 4, -, none)
MMX_EMU_P_MACRO(psubd, int, 2, -, none)

MMX_EMU_P_MACRO(paddsb, char, 8, +, charsigned)
MMX_EMU_P_MACRO(paddsw, short, 4, +, shortsigned)
MMX_EMU_P_MACRO(paddusb, unsigned char, 8, +, charunsigned)
MMX_EMU_P_MACRO(paddusw, unsigned short, 4, +, shortunsigned)

MMX_EMU_P_MACRO(psubsb, char, 8, -, charsigned)
MMX_EMU_P_MACRO(psubsw, short, 4, -, shortsigned)
MMX_EMU_P_MACRO(psubusb, unsigned char, 8, -, charunsigned)
MMX_EMU_P_MACRO(psubusw, unsigned short, 4, -, shortunsigned)

MMX_EMU_P_MACRO(pmullw, short, 4, *, low)
MMX_EMU_P_MACRO(pmulhw, short, 4, *, high)

void pmaddwd(void *src, void *dest) 
{
	short *d = (short *) dest;
	int *dd  = (int *)   dest;
	short *s = (short *) src;
	dd[0] = (int)s[0] * (int)d[0] + (int)s[1] * (int)d[1];		
	dd[1] = (int)s[2] * (int)d[2] + (int)s[3] * (int)d[3];		

	mmx_printf("pmaddwd called\n"); 
}
