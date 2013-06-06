#include <stdio.h>
#include <signal.h>
#include <asm/sigcontext.h>
#include "mmx_emu.h"

extern struct sigcontext * context; 

/* Error */
void MMX_illegal(void *src, void *dest)
{
	mmx_printf("Yuck, this is not for ME !\n");
        signal(SIGILL, SIG_DFL);
        raise(SIGILL);
}

/* EMMS */
void emms(void *src, void *dest)
{
	mmx_printf("emms called\n");
	context->fpstate->tag = 0xffffffff;
}

/* Moves.  Should we duplicate the different opcodes ? */
/* FIXME: memcpy() should not produce optimal code. */

void movq2mem(void *src, void *dest) {
	mmx_printf("movq2mem called\n");
	memcpy(dest, src, 8);
}

/* FIXME: it's DIRTY. */
void movq2mmx(void *src, void *dest) {
	mmx_printf("movq2mmx called\n");
	movq2mem(dest, src);
}

void movd2mem(void *src, void *dest) {
	mmx_printf("movd2mem called\n");
	memcpy(dest, src, 4);
}

void movd2mmx(void *src, void *dest) {
	mmx_printf("movd2mmx called\n");
	movd2mem(dest,src);
}

