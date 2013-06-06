/*
 * Entry code of the MMX emulator:
 * - signal handling
 * - instruction sets detection
 * - initialization
 * Copyright  Sylvain Pion, 1998.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "emu.h"
#include "context.h"
#include "decode.h"

static int mmx_emu_look_ahead, mmx_emu_cyrix_emmx, mmx_emu_amd_3dnow;
int mmx_unit_present, _3DNow_unit_present, emmx_unit_present;
typedef void (*sig_handler_t)(int);

static void mmx_emu_init(void)  __attribute__ ((constructor));
static void mmx_ill_handler(int, sigcontext_t);

static void emmx_test_handler(int i, sigcontext_t sigcontext)
{
	emmx_unit_present = 0;
	sigcontext.eip += 3;
}

// Returns whether EMMX instructions are supported by the proc (and activated).
static inline void detect_emmx(void)
{
	struct sigaction act = {(sig_handler_t) emmx_test_handler,{{0}},0,NULL};

	sigaction(SIGILL, &act, NULL);
	emmx_unit_present = 1;
        __asm__ __volatile__ ( ".byte 0x0f,0x51,0xc0\n" : :); // paddsiw mm0,mm0
}

// Returns whether 3DNow! instructions are supported by the processor */
static inline void detect_3dnow(void)
{
        unsigned int cpuid;

        __asm__ __volatile__ (
		"pushl %%ebx\n\t"
                "movl $0x80000001, %%eax\n\t"
                "cpuid\n\t"
                "movl %%edx, %0\n\t"
		"popl %%ebx"
                : "=d" (cpuid)
                :
		: "ax", "bx", "cx", "dx"
        );
        _3DNow_unit_present = ((cpuid & 0x80000000) != 0);
}

/* Returns whether MMX instructions are supported by the processor */
static inline void detect_mmx(void)
{
        unsigned int cpuid, dummy;

// Strange !!!  If I do not save %ebx manually, it doesn't work, despite
// "bx" in the clobber list.  What's the solution ?  [FIXME]
// Only triggered with -fpic !!!
// BUG-report sent to egcs-bugs on 25/8/98.

        asm const (
		"pushl %%ebx\n\t"
		"cpuid\n\t"
		"popl %%ebx"
		: "=a" (dummy), "=d" (cpuid)
		: "0" (1)
		: "bx", "cx"
        );
	mmx_unit_present = ((cpuid & 0x800000) != 0);
}

// The intialization function.
static void mmx_emu_init(void)
{
	int i;
	struct sigaction act = {(sig_handler_t) mmx_ill_handler,{{0}},0,NULL};

	/* Detecting features. */
#if 0
	detect_mmx();
	detect_3dnow();
	detect_emmx();

	if (mmx_unit_present)
		printf("MMX unit detected\n");
	else
		printf("No MMX unit detected -> Emulator used\n");
	if (_3DNow_unit_present)
		printf("3DNow! unit detected \n");
	else
		printf("No 3DNow! unit detected -> Emulator used\n");
	if (emmx_unit_present)
		printf("EMMX unit detected \n");
	else
		printf("No EMMX unit detected -> Emulator used\n");
#endif
	/* Setting up the SIGILL handler */

	if (sigaction(SIGILL, &act, NULL))
		printf("SIG_ILL handler NOT installed sucessfully.\n");
	else
		mmx_printf("SIG_ILL handler installed by the MMX-emulator.\n");

	/* Check the environment variables. */
	mmx_emu_look_ahead = (getenv("MMX_EMU_NO_LOOK_AHEAD") == NULL);
	mmx_emu_cyrix_emmx = (getenv("MMX_EMU_NO_CYRIX_EMMX") == NULL);
	mmx_emu_amd_3dnow  = (getenv("MMX_EMU_NO_AMD_3DNOW") == NULL);

	/* Drop Cyrix' EMMX support. */
	if (!mmx_emu_cyrix_emmx) {
		for (i=0; i<16; i++)
			mmx_insn[0x50+i] = __BAD;
		mmx_printf("Cyrix EMMX emulation removed.\n");
	};

	/* Drop AMD's 3DNow! support. */
	if (!mmx_emu_amd_3dnow) {
		mmx_insn[0x0d] = mmx_insn[0x0e] = mmx_insn[0x0f] = __BAD;
		mmx_printf("AMD's 3DNow! emulation removed.\n");
	};
}

static int is_in_handler = 0; // Check re-entrancy problems.
static int count_mmx = 0;     // Counter of entrancy ( != nb_insns).

// The SIGILL handler.
// If the application declares another one, it might override this one...
static void mmx_ill_handler(int sig_nr, sigcontext_t sigcontext)
{
	int first_loop = 1;
	context = &sigcontext;

	if (is_in_handler == 1)
		printf("Re-enter the sig-handler... BAD !\n");
	is_in_handler = 1;
	count_mmx++;
	mmx_printf("count=%d\t context=%08lx\t eip=%08lx\t esp=%08lx\n",
			count_mmx, (long) &context, context->eip, context->esp);

	if (sig_nr != SIGILL)  printf("You crazy guy !\n");

	do {
		if (!mmx_decode())
			goto bad_insn;
		first_loop = 0;
	} while (mmx_emu_look_ahead);

	is_in_handler = 0;
	return;

bad_insn:
	if (first_loop) {
		struct sigaction act = {SIG_DFL, {{0}}, 0, NULL};
		printf("Yuck, this SIGILL was not for MMX-emu !\n");
		// We remove the sighandler, and raise SIGILL.
		sigaction(SIGILL, &act, NULL);
		raise(SIGILL);
	};
	is_in_handler = 0;
}
