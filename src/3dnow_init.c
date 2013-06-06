/*
 * Emulation code of the AMD 3DNow!(tm) init functions.
 * (C) Oliver Delise <delise@online-club.de>, 1998, LGPL
 */

#include "emu.h"
#include "context.h"

void femms(void *src, void *dest)
{
	context->fpstate->tag = 0xffffffff;
	mmx_printf("femms called\n");
}

void prefetch(void *src, void *dest)
{
	mmx_printf("prefetch called\n");
}
