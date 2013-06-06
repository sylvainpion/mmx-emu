/*
 * Emulation code of the AMD 3DNow!(tm) "transcendental" functions.
 * Copyright  Sylvain Pion, 1998.
 */

#include <stdio.h>
#include <math.h>
#include "emu.h"

// Our emulated approximation is already the good result :-),
// so the Newton-Raphson steps are empty (only a check).
// Maybe better do pfrcpit1 = pfrcpit2 = pfrcp.
void pfrcp(void *src, void *dest)
{
	float *s = (float *) src;
	float *d = (float *) dest;

	d[0] = 1/s[0];
	d[1] = 1/s[1];
	mmx_printf("pfrcp called\n");
}

void pfrcpit1(void *src, void *dest)
{
	float *s = (float *) src;
	float *d = (float *) dest;

	if ((d[0] != 1/s[0]) || (d[1] != 1/s[1]))
		printf("mmx-emu: warning, maybe using pfrcpit1 not the way we thought.\n");

// NB: must we do dest = src ?
	mmx_printf("pfrcpit1 called\n");
}

void pfrcpit2(void *src, void *dest)
{
	float *s = (float *) src;
	float *d = (float *) dest;

	if ((d[0] != 1/s[0]) || (d[1] != 1/s[1]))
		printf("mmx-emu: warning, maybe using pfrcpit2 not the way we thought.\n");
// NB: must we do dest = src ?
	mmx_printf("pfrcpit2 called\n");
}

void pfrsqrt(void *src, void *dest)
{
	float *s = (float *) src;
	float *d = (float *) dest;

	d[0] = 1/sqrt((double) fabs(s[0]));
	if (s[0] < 0)  d[0] = -d[0];
	d[1] = d[0];
	mmx_printf("pfrsqrt called\n");
}

void pfrsqit1(void *src, void *dest)
{
	float *s = (float *) src;
	float *d = (float *) dest;
	float test = 1/sqrt((double) fabs(s[0]));

	if (s[0] < 0)  test = -test;
	if ((d[0] != test) || (d[1] != test))
		printf("mmx-emu: warning, maybe using pfrsqit1 not the way we thought.\n");
// NB: must we do dest = src ?
	mmx_printf("pfrsqit1 called\n");
}
