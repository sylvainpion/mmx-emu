/*
 * Main code of the MMX emulator (signal handler, opcode decoding).
 * Copyright  Sylvain Pion, July 1998.
 */

#include <stdio.h>
#include <signal.h>
#include <asm/sigcontext.h>
#include "mmx_emu.h"
#include "mmx_arithmetic.h"
#include "mmx_logical.h"
#include "mmx_shift.h"
#include "mmx_conversion.h"
#include "mmx_comparison.h"

#define __BAD  MMX_illegal
#define u_char unsigned char

int pshi_diff; // Used temporarily to differentiate pshi*.
struct sigcontext * context;
#define REG_(reg) (*((&(context->eax)) - (reg)))

void mmx_emu_main(void)  __attribute__ ((constructor));
void mmx_ill_handler(int);
static int sib(int mod, unsigned * mmx_eip);

/* 57 base MMX instructions.
 * Refer to http://developer.intel.com/drg/mmx/manuals/prm/PRM_APPD.HTM
 * http://www.imada.ou.dk/~jews/PInfo/mmx.html  is interesting too.
 */

static FUNC const mmx_insn[256] = {
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 0 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 1 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 2 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 3 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 4 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 5 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
/* Here: cmps, [un]pack, pshi* (consts shifts), emms, mov[dq] */
/* 0-8 ,  1-9  ,  2-a  ,  3-b  ,  4-c  ,  5-d  ,  6-e  ,  7-f  */
punpcklbw,punpcklwd,punpckldq,packsswb,pcmpgtb,pcmpgtw,pcmpgtd,packuswb, /* 6 */
punpckhbw,punpckhwd,punpckhdq,packssdw,__BAD,__BAD,movd2mem,movq2mem   ,
__BAD  ,pshimw ,pshimd ,pshimq ,pcmpeqb,pcmpeqw,pcmpeqd,emms   , /* 7 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,movd2mmx   ,movq2mmx   ,
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
/* 0-8 ,  1-9  ,  2-a  ,  3-b  ,  4-c  ,  5-d  ,  6-e  ,  7-f  */
};

// This function is adapted from the (kernel land) FPU-emulator.
static int sib(int mod, unsigned * mmx_eip)
{
  u_char ss,index,base;
  long offset;

  base = *((u_char *) (*mmx_eip));   /* The SIB byte */
  //(*mmx_eip)++;
  ss = base >> 6;
  index = (base >> 3) & 7;
  base &= 7;

  if ((mod == 0) && (base == 5))
    offset = 0;              /* No base register */
  else {
    offset = REG_(base);
    mmx_printf("Base register: %d    (offset = %ld)\n", base, offset);
  };

  if (index == 4)
    {
      /* No index register */
      /* A non-zero ss is illegal */
      if ( ss )
	printf("MMX-Emulator error...\n");
        // EXCEPTION(EX_Invalid);
    }
  else
    {
      offset += (REG_(index)) << ss;
      mmx_printf("Index register: %d\n", index);
      mmx_printf("Scale factor: %d    (offset = %ld)\n", ss, offset);
    }

  if (mod == 1)
    {
      /* 8 bit signed displacement */
      long displacement;
      displacement = *((signed char *) (*mmx_eip));
      // offset += displacement;
      offset = displacement;
      (*mmx_eip)++;
    }
  else if (mod == 2 || base == 5) /* The second condition also has mod==0 */
    {
      /* 32 bit displacement */
      long displacement;
      displacement = *((long *) (*mmx_eip));
      offset += displacement;
      (*mmx_eip) += 4;
    }

  mmx_printf("offset = %ld\n", offset);
  return offset;
}

void mmx_emu_main(void)
{
        if (SIG_ERR == signal(SIGILL, mmx_ill_handler))
                printf("SIG_ILL handler not installed sucessfully.\n");
#ifdef MMX_DEBUG
        printf("SIG_ILL handler installed by the MMX-emulator.\n");
#endif
}


/* Here's the SIGILL handler.
 * If the application declares another one, it might override this one...
 * Also to speed up, we might use sigaction, with well thought flags.
 */

void mmx_ill_handler(int sig_nr)
{
/* pipo HAS TO STAY EXACTLY HERE, till a cleaner solution is found. */
	int pipo;
	int i, j;
	unsigned rm, mmx_eip;
	u_char prefix, insn, modrm, mod; // sib;
	void *src = NULL, *dest = NULL;
	unsigned long long immediate;

/* Is there a cleaner way for that ? */
	context = (struct sigcontext *) (&pipo + 4);
	mmx_eip = context->eip;

	if (sig_nr != SIGILL)  printf("You crazy guy !\n");

    do {   /* Look-ahead loop */

/* Prints the whole context. */
        mmx_printf("context      = %08lx\n", (long) context);

	for (i=0; i<(sizeof(struct sigcontext)/4); i++)
		mmx_printf("%08lx", ((long *) context)[i]);
	mmx_printf("\n");

/* Prints the whole FPU/MMX registers.  */
	for (i=0; i<8; i++) {
		mmx_printf("%%mm%d = ", i);
		for (j=3; j>=0; j--)
		    mmx_printf("%04x", context->fpstate->_st[i].significand[j]);
		mmx_printf(" %04x", context->fpstate->_st[i].exponent);
		mmx_printf((i&1) ? "\n" : "\t");
	}

/* Prints the opcodes, byte by byte. */
        mmx_printf("EIP = %08lx (code: %02x %02x %02x %02x %02x %02x %02x %02x)\n",
		mmx_eip,
		((u_char *) mmx_eip)[0], ((u_char *) mmx_eip)[1],
		((u_char *) mmx_eip)[2], ((u_char *) mmx_eip)[3],
		((u_char *) mmx_eip)[4], ((u_char *) mmx_eip)[5],
		((u_char *) mmx_eip)[6], ((u_char *) mmx_eip)[7]);
	
	prefix = ((u_char *) mmx_eip)[0];
	++mmx_eip;
	if (prefix != 0x0f) {
		goto not_for_mmx_emu;
		// MMX_illegal(NULL,NULL);
	} else {
		insn = ((u_char *) mmx_eip)[0];
		++mmx_eip;
		if (mmx_insn[insn] != emms) { /* We could avoid this test... */
			modrm = ((u_char *) mmx_eip)[0];
			++mmx_eip;
			rm = modrm & 7;
			mod = (modrm >> 6) & 3;
			switch (mod) {
			case 3: /* Dirty, dirty, dirty... */
				if ( (mmx_insn[insn] == pshimw) ||
				     (mmx_insn[insn] == pshimd) ||
				     (mmx_insn[insn] == pshimq) )
				{
					++mmx_eip;
					immediate = *(unsigned char*)mmx_eip;
					pshi_diff = (modrm>>3)&7;
					src  = &immediate;
					dest = &(context->fpstate->_st[rm]);
				} else {
					src  = &(context->fpstate->_st[rm]);
					dest = &(context->fpstate->_st[(modrm>>3) & 7]);
				};
	mmx_printf("src  = %08lx (%%mm%d)\t", (long) src, rm);
	mmx_printf("dest = %08lx (%%mm%d)\n", (long) dest, (modrm>>3) & 7);
				break;
			case 1:
	/* dest is always an mmxreg, except for mov[dq]2mem */
	/* See FPU_get_address() and sib() in get_Adress.c (math-emu) */
				src = REG_(rm) + sib(mod, &mmx_eip);
				dest = &(context->fpstate->_st[(modrm>>3) & 7]);
	mmx_printf("src register -> %d\n", rm);
	mmx_printf("src  = %08lx \t", (long) src);
	mmx_printf("dest = %08lx (%%mm%d)\n", (long) dest, (modrm>>3) & 7);
				break;
			default:
				printf("ModR/M unknown: %08x\n", modrm);
				++mmx_eip; // Just a guess to continue.
			};
			context->fpstate->tag = 0;
		};
		// Let's execute the instruction now.
		mmx_insn[insn](src, dest);
	};
	
	mmx_printf("New EIP: %08lx\n", mmx_eip);
	context->eip = mmx_eip;

    } while(1);

not_for_mmx_emu:

        if (SIG_ERR == signal(SIGILL, mmx_ill_handler))
                printf("SIG_ILL handler not re-installed sucessfully.\n");

	mmx_printf("----- exiting MMX-Emu sigill handler\n");
	return;
}
