/*
 * Emulation code of the comparison functions.
 */

#include "mmx_emu.h"

void pcmpeqb(void *src, void *dest) {
	char *d = (char *) dest;
	char *s = (char *) src;
	d[0] = (d[0] == s[0]) ? -1 : 0;
	d[1] = (d[1] == s[1]) ? -1 : 0;
	d[2] = (d[2] == s[2]) ? -1 : 0;
	d[3] = (d[3] == s[3]) ? -1 : 0;
	d[4] = (d[4] == s[4]) ? -1 : 0;
	d[5] = (d[5] == s[5]) ? -1 : 0;
	d[6] = (d[6] == s[6]) ? -1 : 0;
	d[7] = (d[7] == s[7]) ? -1 : 0;
	mmx_printf("pcmpeqb called\n");
}

void pcmpeqw(void *src, void *dest) {
	short *d = (short *) dest;
	short *s = (short *) src;
	d[0] = (d[0] == s[0]) ? -1 : 0;
	d[1] = (d[1] == s[1]) ? -1 : 0;
	d[2] = (d[2] == s[2]) ? -1 : 0;
	d[3] = (d[3] == s[3]) ? -1 : 0;
	mmx_printf("pcmpeqw called\n");
}

void pcmpeqd(void *src, void *dest) {
	int *d = (int *) dest;
	int *s = (int *) src;
	d[0] = (d[0] == s[0]) ? -1 : 0;
	d[1] = (d[1] == s[1]) ? -1 : 0;
	mmx_printf("pcmpeqd called\n");
}


void pcmpgtb(void *src, void *dest) {
	char *d = (char *) dest;
	char *s = (char *) src;
	d[0] = (d[0] > s[0]) ? -1 : 0;
	d[1] = (d[1] > s[1]) ? -1 : 0;
	d[2] = (d[2] > s[2]) ? -1 : 0;
	d[3] = (d[3] > s[3]) ? -1 : 0;
	d[4] = (d[4] > s[4]) ? -1 : 0;
	d[5] = (d[5] > s[5]) ? -1 : 0;
	d[6] = (d[6] > s[6]) ? -1 : 0;
	d[7] = (d[7] > s[7]) ? -1 : 0;
	mmx_printf("pcmpgqb called\n");
}

void pcmpgtw(void *src, void *dest) {
	short *d = (short *) dest;
	short *s = (short *) src;
	d[0] = (d[0] > s[0]) ? -1 : 0;
	d[1] = (d[1] > s[1]) ? -1 : 0;
	d[2] = (d[2] > s[2]) ? -1 : 0;
	d[3] = (d[3] > s[3]) ? -1 : 0;
	mmx_printf("pcmpgqw called\n");
}

void pcmpgtd(void *src, void *dest) {
	int *d = (int *) dest;
	int *s = (int *) src;
	d[0] = (d[0] > s[0]) ? -1 : 0;
	d[1] = (d[1] > s[1]) ? -1 : 0;
	mmx_printf("pcmpgqd called\n");
}
