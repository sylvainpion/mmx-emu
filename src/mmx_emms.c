/*
 * Emulation of the EMMS opcode.
 * Copyright  Sylvain Pion, 1998.
 */

#include "emu.h"
#include "context.h"

void emms(void *src, void *dest)
{
	context->fpstate->tag = 0xffffffff;
	mmx_printf("emms called\n");
}
