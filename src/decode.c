/*
 * Opcode and operand decoding.
 * Copyright  Sylvain Pion, 1998.
 */

#include <stdio.h>
#include "context.h"
#include "emu.h"
#include "decode.h"
#include "mmx_emms.h"
#include "mmx_moves.h"
#include "mmx_arithmetic.h"
#include "mmx_logical.h"
#include "mmx_shift.h"
#include "mmx_conversion.h"
#include "mmx_comparison.h"
#include "emmx_cyrix.h"
#include "3dnow_decode.h"
#include "3dnow_init.h"

#define u_char unsigned char

// FIXME: Those global vars are bad if we emulate a multi-threaded program...

int pshi_diff; // Used temporarily to differentiate pshi*.
sigcontext_t * context;

static void * sib(int, unsigned *);
static inline char disp8(unsigned *);
static inline int disp32(unsigned *);

/* 57 base MMX instructions.  More information in:
 * http://developer.intel.com/drg/mmx/manuals/prm/prm.htm
 * http://www.imada.ou.dk/~jews/PInfo/mmx.html  is interesting too.
 * 12 Cyrix-EMMX insns (cf ftp://ftp.cyrix.com/6x86MX/docs/108ap.pdf)
 */

FUNC mmx_insn[256] = {
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 0 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD ,prefetch,femms  ,_3dnow ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 1 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 2 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 3 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 4 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
/* Cyrix' EMMX stuff (disabled when MMX_EMU_NO_CYRIX_EMMX is set). */
paveb  ,paddsiw,pmagw  ,__BAD  ,pdistib,psubsiw,__BAD  ,__BAD  , /* 5 */
pmvzb  ,pmulhrw,pmvnzb ,pmvlzb,pmvgezb,pmulhriw,pmachriw,__BAD ,
/* 0/8 ,  1/9  ,  2/a  ,  3/b  ,  4/c  ,  5/d  ,  6/e  ,  7/f  */
/* Here: cmps, [un]pack, pshi* (consts shifts), emms, mov[dq] */
punpcklbw,punpcklwd,punpckldq,packsswb,pcmpgtb,pcmpgtw,pcmpgtd,packuswb, /* 6 */
punpckhbw,punpckhwd,punpckhdq,packssdw,__BAD,__BAD,movd2mmx,movq2mmx,
__BAD  ,pshimw ,pshimd ,pshimq ,pcmpeqb,pcmpeqw,pcmpeqd,emms   , /* 7 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,movd2mem,movq2mem,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 8 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 9 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* a */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* b */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* c */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
/* Here: arith, shifts, logic */
__BAD  ,psrlw  ,psrld  ,psrlq  ,__BAD  ,pmullw ,__BAD  ,__BAD  , /* d */
psubusb,psubusw,__BAD  ,pand   ,paddusb,paddusw,__BAD  ,pandn  ,
__BAD  ,psraw  ,psrad  ,__BAD  ,__BAD  ,pmulhw ,__BAD  ,__BAD  , /* e */
psubsb ,psubsw ,__BAD  ,por    ,paddsb ,paddsw ,__BAD  ,pxor   ,
__BAD  ,psllw  ,pslld  ,psllq  ,__BAD  ,pmaddwd,__BAD  ,__BAD  , /* f */
psubb  ,psubw  ,psubd  ,__BAD  ,paddb  ,paddw  ,paddd  ,__BAD  
/* 0/8 ,  1/9  ,  2/a  ,  3/b  ,  4/c  ,  5/d  ,  6/e  ,  7/f  */
};

static void * sib(int mod, unsigned * mmx_eip)
{
  u_char ss,index,base;
  void * offset;

  base = *((u_char *) (*mmx_eip));   /* The SIB byte */
  (*mmx_eip)++;
  ss = base >> 6;
  index = (base >> 3) & 7;
  base &= 7;

  mmx_printf("base=%d\tss=%d\tindex=%d\n", base, ss, index);

  if ((mod == 0) && (base == 5))
    offset = 0;              /* No base register */
  else
    offset = * (void **) REG_(base);

  if (index == 4) {
      if ( ss ) // This test is in the FPU-emu and real-life, but not in specs!
	printf("MMX-Emulator error (bad address)\n");
  }
  else
      offset += (*(int*)REG_(index)) << ss;

/*
  if (mod == 1)
      offset += disp8(mmx_eip);
  else if (mod == 2 || base == 5) // The second condition also has mod==0
      offset += disp32(mmx_eip);
*/

  mmx_printf("sib offset = %08lx\n", (long) offset);
  return offset;
}

// Computes a 8-bit displacement.
static inline char disp8(unsigned * mmx_eip)
{
	char disp = *((char *) (*mmx_eip));
	(*mmx_eip)++;
	return disp;
}

// Computes a 32-bit displacement.
static inline int disp32(unsigned * mmx_eip)
{
	int disp = *((int *) (*mmx_eip));
	(*mmx_eip)+=4;
	return disp;
}


void __BAD(void *src, void *dest)
{
	printf("We should NOT go here !\n");
}


// Main decoding function.

int mmx_decode(void)
{
	int i, j;
	unsigned rm, mmx_eip;
	u_char prefix, insn, modrm, mod, reg;
	void *src = NULL, *dest = NULL;
	unsigned long long imm8;

	mmx_eip = context->eip;

/* Prints the whole context. */
        mmx_printf("\n\ncontext      = %08lx\n", (long) context);
	for (i=0; i<(sizeof(*context)/4); i++)
		mmx_printf("%08lx", ((long *) context)[i]);
	mmx_printf("\n");

/* Prints the whole FPU/MMX registers.  */
	for (i=0; i<8; i++) {
		mmx_printf("%%mm%d = ", i);
		for (j=3; j>=0; j--)
			mmx_printf("%04x", MMX_REG_ADR(i)->significand[j]);
		mmx_printf(" %04x", MMX_REG_ADR(i)->exponent);
		mmx_printf((i&1) ? "\n" : "\t");
	}

/* Prints the opcodes, byte by byte. */
        mmx_printf(
		"EIP = %04x (code: %02x %02x %02x %02x %02x %02x %02x %02x)\n",
		mmx_eip,
		((u_char *) mmx_eip)[0], ((u_char *) mmx_eip)[1],
		((u_char *) mmx_eip)[2], ((u_char *) mmx_eip)[3],
		((u_char *) mmx_eip)[4], ((u_char *) mmx_eip)[5],
		((u_char *) mmx_eip)[6], ((u_char *) mmx_eip)[7]);


	prefix = *(u_char *) mmx_eip;
	++mmx_eip;
	if (prefix != 0x0f)
		goto bad_insn;

	insn = *(u_char *) mmx_eip;
	++mmx_eip;
	if (mmx_insn[insn] == __BAD)
		goto bad_insn;
	if ((mmx_insn[insn] != emms) &&
	    (mmx_insn[insn] != femms) &&
	    (mmx_insn[insn] != prefetch))
	{  // We decode the following only if != (emms, femms, prefetch).
		modrm = *(u_char *) mmx_eip;
		++mmx_eip;
		rm = modrm & 7;
		reg = (modrm >> 3) & 7;
		mod = (modrm >> 6) & 3;
		mmx_printf("mod=%d\trm=%d\treg=%d\n", mod, rm, reg);
// Do the adress decoding, cf table 25-3 and 25-4 in Intel's 241430_4.pdf.
		switch (mod) {
// dest is always an mmxreg, except for mov[dq]2mem 
		case 0:
			if (rm==4)	src = sib(mod, &mmx_eip);
			else if (rm==5)	src = (void *) disp32(&mmx_eip);
			else		src = (void *) *REG_(rm);
			dest = MMX_REG_ADR(reg);
			break;
		case 1:
			if (rm==4)	src = sib(mod, &mmx_eip);
			else		src = (void *) *REG_(rm);
			src += disp8(&mmx_eip);
			dest = MMX_REG_ADR(reg);
			break;
		case 2:
			if (rm==4)	src = sib(mod, &mmx_eip);
			else		src = (void *) *REG_(rm);
			src += disp32(&mmx_eip);
			dest = MMX_REG_ADR(reg);
			break;
		case 3: // This case is still a bit dirty.
			if ( (mmx_insn[insn] == pshimw) ||
			     (mmx_insn[insn] == pshimd) ||
			     (mmx_insn[insn] == pshimq) )
			{
				imm8 = *(u_char*) mmx_eip;
				++mmx_eip;
				pshi_diff = reg;
				src  = &imm8;
				dest = MMX_REG_ADR(rm);
			} else if (mmx_insn[insn] == _3dnow) {
				imm8 = *(u_char*) mmx_eip;
				_3dnow_suffix = imm8;
				++mmx_eip;
			} else {
				src  = MMX_REG_ADR(rm);
				dest = MMX_REG_ADR(reg);
			};
			break;
		default:
			printf("Unknown ModR/M: %08x\n", modrm);
			goto bad_insn;
		};
		context->fpstate->tag = 0;

		mmx_printf("src  = %08lx (~%%mm%d)\t", (long) src, rm);
		mmx_printf("dest = %08lx (~%%mm%d)\n", (long) dest, reg);
	} else if (mmx_insn[insn] == prefetch) {
		++mmx_eip;
	};

	mmx_printf("ebp= %08lx (adr = %08lx)\n", context->ebp,
			(long) &(context->ebp));
	mmx_printf("esp= %08lx (adr = %08lx)\n", context->esp,
			(long) &(context->esp));

	// Ok, let's execute the instruction now.
	mmx_insn[insn](src, dest);
	context->fpstate->status &= 0xffffe3ffL;

	mmx_printf("New EIP: %04x\n", mmx_eip);
	context->eip = mmx_eip;
	return 1;

bad_insn:
	return 0;
}
