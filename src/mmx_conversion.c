/*
 * Emulation code of the conversion functions.
 * (C) Oliver Delise <delise@online-club.de>, July 1998, LGPL
 */

#include "mmx_emu.h"

#define MMX_EMU_L_CON_MACRO(NAME, TYPE, LOOP)		\
void NAME (void *src, void *dest) {			\
	int i;						\
	TYPE *d = (TYPE *) dest;			\
	TYPE *s = (TYPE *) src;				\
	for (i=LOOP-1; i >= 0; i--) {			\
		d[2*i+1] = s[i];			\
		d[2*i]   = d[i];			\
	};						\
	mmx_printf(#NAME " called\n");			\
}

#define MMX_EMU_H_CON_MACRO(NAME, TYPE, LOOP)		\
void NAME (void *src, void *dest) {			\
	int i;						\
	TYPE *d = (TYPE *) dest;			\
	TYPE *s = (TYPE *) src;				\
	for (i=0; i < LOOP; i++){			\
		d[2*i]   = d[i+LOOP];			\
		d[2*i+1] = s[i+LOOP];			\
	}						\
	mmx_printf(#NAME " called\n");			\
}


MMX_EMU_L_CON_MACRO(punpcklbw, char , 4);
MMX_EMU_L_CON_MACRO(punpcklwd, short, 2);
MMX_EMU_L_CON_MACRO(punpckldq, int  , 1);

MMX_EMU_H_CON_MACRO(punpckhbw, char , 4);
MMX_EMU_H_CON_MACRO(punpckhwd, short, 2);
MMX_EMU_H_CON_MACRO(punpckhdq, int  , 1);


void packsswb(void *src, void *dest)
{
	short *dd = (short *) dest;
	short *ss = (short *) src;
	char  *d  = (char *)  dest;
	char  *s  = (char *)  src;

/* I find this one more readable, but maybe it's slower.

	int i;
	for (i=0; i<4; i++) 
	{
		if (dd[i] > 0x7f)       d[i] = 0x7f;
		else if (dd[i] < -0x80) d[i] = -0x80;
	}

	for (i=0; i<4; i++) 
	{
		if (ss[i] > 0x7f)       d[i+4] = 0x7f;
		else if (ss[i] < -0x80) {
					d[i+4] = -0x80; }
		else 			d[i+4] = s[2*i];
	}
*/
	d[0] = ((dd[0]+0x80) & 0xff00) ? 0x80-!(d[1]>>8) : d[0];
	d[1] = ((dd[1]+0x80) & 0xff00) ? 0x80-!(d[3]>>8) : d[2];
	d[2] = ((dd[2]+0x80) & 0xff00) ? 0x80-!(d[5]>>8) : d[4];
	d[3] = ((dd[3]+0x80) & 0xff00) ? 0x80-!(d[7]>>8) : d[6]; 
	d[4] = ((ss[0]+0x80) & 0xff00) ? 0x80-!(s[1]>>8) : s[0];
	d[5] = ((ss[1]+0x80) & 0xff00) ? 0x80-!(s[3]>>8) : s[2];
	d[6] = ((ss[2]+0x80) & 0xff00) ? 0x80-!(s[5]>>8) : s[4];
	d[7] = ((ss[3]+0x80) & 0xff00) ? 0x80-!(s[7]>>8) : s[6]; 
	mmx_printf("packsswb called\n");
}

void packuswb(void *src, void *dest)
{ 
	char *d = (char *) dest;
	char *s = (char *) src;
	
	d[0] = (d[1]) ? -!(d[1]>>8) : d[0];
	d[1] = (d[3]) ? -!(d[3]>>8) : d[2];
	d[2] = (d[5]) ? -!(d[5]>>8) : d[4];
	d[3] = (d[7]) ? -!(d[7]>>8) : d[6];
	d[4] = (s[1]) ? -!(s[1]>>8) : s[0];
	d[5] = (s[3]) ? -!(s[3]>>8) : s[2];
	d[6] = (s[5]) ? -!(s[5]>>8) : s[4];
	d[7] = (s[7]) ? -!(s[7]>>8) : s[6];
	mmx_printf("packuswb called\n");
}

void packssdw(void *src, void *dest)
{
	int   *dd = (int *)   dest;
	int   *ss = (int *)   src;
	short *d  = (short *) dest;
	short *s  = (short *) src;

	d[0] = ((dd[0]+0x8000) & 0xffff0000) ? 0x8000-!(d[1]>>16) : d[0];
	d[1] = ((dd[1]+0x8000) & 0xffff0000) ? 0x8000-!(d[3]>>16) : d[2];
	d[2] = ((ss[0]+0x8000) & 0xffff0000) ? 0x8000-!(s[1]>>16) : s[0];
	d[3] = ((ss[1]+0x8000) & 0xffff0000) ? 0x8000-!(s[3]>>16) : s[2];
	mmx_printf("packssdw called\n");
}
