/*
 * Emulation code of the arithmetic functions.
 */

#include "mmx_emu.h"

void paddusb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void paddusw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void paddsb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void paddsw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void paddb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void paddw(void *src, void *dest) { 
        short *d = (short *) dest;
        short *s = (short *) src;
	d[0] += s[0];
	d[1] += s[1];
	d[2] += s[2];
	d[3] += s[3];
        mmx_printf("paddw called\n"); 
}

void paddd(void *src, void *dest) {
        int *d = (int *) dest;
        int *s = (int *) src;
	d[0] += s[0];
	d[1] += s[1];
        mmx_printf("paddd called\n");
}

void psubusb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubusw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubsb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubsw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubb(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void psubd(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void pmullw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void pmulhw(void *src, void *dest) { mmx_printf("MMX function called\n"); }
void pmaddwd(void *src, void *dest) { mmx_printf("MMX function called\n"); }

