/*
 * Emulation code of the AMD 3DNow!(tm) arithmetic functions.
 * (C) Oliver Delise <delise@online-club.de>, 1998, LGPL
 */

#include "emu.h"

#define MMX_EMU_3dn_ARI_MACRO(NAME, SYMB, OPS, OPD)	\
void NAME (void *src, void *dest) {			\
	float *d = (float *) dest;			\
	float *s = (float *) src;			\
							\
	d[0] = OPD[0] SYMB OPS[0];			\
	d[1] = OPD[1] SYMB OPS[1];			\
	mmx_printf(#NAME " called\n");			\
}

MMX_EMU_3dn_ARI_MACRO(pfadd,  +, s, d)
MMX_EMU_3dn_ARI_MACRO(pfmul,  *, s, d)
MMX_EMU_3dn_ARI_MACRO(pfsub,  -, s, d)
MMX_EMU_3dn_ARI_MACRO(pfsubr, -, d ,s)


#define MMX_EMU_3dn_ARI_minmax_MACRO(NAME, SYMB)	\
void NAME (void *src, void *dest) {			\
	float *d = (float *) dest;			\
	float *s = (float *) src;			\
							\
	if (s[0] SYMB d[0]) d[0] = s[0];		\
	if (s[1] SYMB d[1]) d[1] = s[1];		\
	mmx_printf(#NAME " called\n");			\
}

MMX_EMU_3dn_ARI_minmax_MACRO(pfmin, <)
MMX_EMU_3dn_ARI_minmax_MACRO(pfmax, >)


#define MMX_EMU_3dn_ARI_integer_MACRO(NAME, TYPE, LOOP, OP, OFFSET, SHIFT) \
void NAME (void *src, void *dest) {					\
	int i;								\
	TYPE *d = (TYPE *) dest;					\
	TYPE *s = (TYPE *) src;						\
	for (i=0; i < LOOP; i++){					\
		d[i] = ((d[i] OP s[i]) + OFFSET) >> SHIFT;		\
	}								\
	mmx_printf(#NAME " called\n");					\
}

MMX_EMU_3dn_ARI_integer_MACRO(pfmulhrw,        short,  4, *, 0x8000, 16)

void pfacc (void *src, void *dest) {
	float *d = (float *) dest;
	float *s = (float *) src;

	d[0] = d[0] + d[1];
	d[1] = s[0] + s[1];
	mmx_printf("pfacc called\n");
}

void pavgusb(void *src, void *dest) {
	int i;
	unsigned char *d = (unsigned char *) dest;
	unsigned char *s = (unsigned char *) src;
	for (i=0; i < 8; i++)
		d[i] = (((unsigned int) d[i] + (unsigned int) s[i]) + 1) >> 1;
	mmx_printf("pavgusb called\n");
}

// We avoid the conflict with Cyrix'pmulhrw by adding _3dnow.
void pmulhrw_3dnow (void *src, void *dest) {
	int i;
	short *d = (short *) dest;
	short *s = (short *) src;
	for (i=0; i < 4; i++)
		d[i] = (((int)d[i] * (int)s[i]) + 0x8000) >> 16;
	mmx_printf("pmulhrw_3dnow called\n");
}
