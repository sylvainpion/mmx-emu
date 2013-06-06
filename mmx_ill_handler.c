#include <stdio.h>
#include <signal.h>
#include <asm/sigcontext.h>
#include "mmx_emu.h"
#include "mmx_arithmetic.h"
#include "mmx_logical.h"
#include "mmx_shift.h"
#include "mmx_conversion.h"
#include "mmx_comparison.h"

/* Here's the SIGILL handler.
 * If the application declares another one, it might override this one...
 * Also to speed up, we might use sigaction, with well thought flags.
 */

#define __BAD  MMX_illegal
#define u_char unsigned char


/* 52 non-bad insns (there should be 57, no ???).
 * Refer to http://developer.intel.com/drg/mmx/manuals/prm/PRM_APPD.HTM
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

struct sigcontext * context;
#define REG_(reg) (*((&(context->eax)) - (reg)))

// This function is adapted from the (kernel land) FPU-emulator.
static int sib(int mod, unsigned long *mmx_eip)
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
#ifdef MMX_DEBUG
    printf("Base register: %d    (offset = %ld)\n", base, offset);
#endif
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
#ifdef MMX_DEBUG
      printf("Index register: %d\n", index);
      printf("Scale factor: %d    (offset = %ld)\n", ss, offset);
#endif
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

#ifdef MMX_DEBUG
  printf("offset = %ld\n", offset);
#endif
  return offset;
}

void mmx_emu_main(void)  __attribute__ ((constructor));
void mmx_ill_handler(int);

void mmx_emu_main(void)
{
        if (SIG_ERR == signal(SIGILL, mmx_ill_handler))
                printf("SIG_ILL handler not installed sucessfully.\n");
}

// The SIGILL handler properly.
void mmx_ill_handler(int sig_nr)
{
	int pipo;
	int i, j;
	unsigned long mmx_eip;
	u_char prefix, insn, modrm, mod; // sib;
	unsigned rm;
	void *src = NULL, *dest = NULL;

	context = (struct sigcontext *) (&pipo + 4);
		// Is there a cleaner way for that ?

	if (sig_nr != SIGILL)  printf("You crazy guy !\n");

/* Prints the whole context.
        printf("context      = %08lx\n", (long) context);

	for (i=0; i<(sizeof(struct sigcontext)/4); i++)
		printf("%08lx", ((long *) context)[i]);
	printf("\n");
*/

/* Prints the whole FPU/MMX registers.  */
#ifdef MMX_DEBUG
	for (i=0; i<8; i++) {
		printf("%%mm%d = ", i);
		for (j=3; j>=0; j--)
			printf("%04x", context->fpstate->_st[i].significand[j]);
		printf(" %04x", context->fpstate->_st[i].exponent);
		printf((i&1) ? "\n" : "\t");
	}
#endif

	mmx_eip = context->eip;
#ifdef MMX_DEBUG
        printf("EIP = %08lx (code: %02x %02x %02x %02x %02x %02x %02x %02x)\n",
		mmx_eip,
		((u_char *) mmx_eip)[0], ((u_char *) mmx_eip)[1],
		((u_char *) mmx_eip)[2], ((u_char *) mmx_eip)[3],
		((u_char *) mmx_eip)[4], ((u_char *) mmx_eip)[5],
		((u_char *) mmx_eip)[6], ((u_char *) mmx_eip)[7]);
#endif
	
	prefix = ((u_char *) mmx_eip)[0];
	++mmx_eip;
	if (prefix != 0x0f) {
		MMX_illegal(NULL,NULL);
	} else {
		insn = ((u_char *) mmx_eip)[0];
		++mmx_eip;
		if (mmx_insn[insn] != emms) { /* We could avoid this test... */
			modrm = ((u_char *) mmx_eip)[0];
			++mmx_eip;
			rm = modrm & 7;
			mod = (modrm >> 6) & 3;
			switch (mod) {
			case 3: /* Source and dest are mmx registers. */
				src  = &(context->fpstate->_st[rm]);
				dest = &(context->fpstate->_st[(modrm>>3) & 7]);
#ifdef MMX_DEBUG
				printf("src  = %08lx (%%mm%d)\t", (long) src, rm);
				printf("dest = %08lx (%%mm%d)\n", (long) dest, (modrm>>3) & 7);
#endif
				break;
			case 1: /* dest is always an mmxreg, except for mov[dq]2mem */
/* See FPU_get_address() and sib() in get_Adress.c (math-emu) */
				src = REG_(rm) + sib(mod, &mmx_eip);
				dest = &(context->fpstate->_st[(modrm>>3) & 7]);
#ifdef MMX_DEBUG
				printf("src register -> %d\n", rm);
				printf("src  = %08lx \t", (long) src);
				printf("dest = %08lx (%%mm%d)\n", (long) dest, (modrm>>3) & 7);
#endif
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
	
	// Point to the next insn. (FIXME: if successful only)
#ifdef MMX_DEBUG
	printf("New EIP: %08lx\n", mmx_eip);
#endif
	context->eip = mmx_eip;

        if (SIG_ERR == signal(SIGILL, mmx_ill_handler))
                printf("SIG_ILL handler not re-installed sucessfully.\n");

#ifdef MMX_DEBUG
	printf("-----\n");
#endif
	return;
}
