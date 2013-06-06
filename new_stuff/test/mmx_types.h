/* Some Defs are shamelessly stolen by OLK delise@online-club.de 

	The type of an value that fits in an MMX register
	(note that long long constant values MUST be suffixed
	 by LL and unsigned long long values by ULL, lest
	 they be truncated by the compiler)
*/


#include <math.h>

typedef	union {
	long long		q;	/* Quadword (64-bit) value */
	unsigned long long	uq;	/* Unsigned Quadword */
	int			d[2];	/* 2 Doubleword (32-bit) values */
	unsigned int		ud[2];	/* 2 Unsigned Doubleword */
	short			w[4];	/* 4 Word (16-bit) values */
	unsigned short		uw[4];	/* 4 Unsigned Word */
	char			b[8];	/* 8 Byte (8-bit) values */
	unsigned char		ub[8];	/* 8 Unsigned Byte */
	float			f[2];   /* Float (32-bit) single precision */
} mmx_t;

#include "mmx_arithmetic.h"
#include "mmx_comparison.h"
#include "mmx_conversion.h"
#include "mmx_logical.h"
#include "mmx_shift.h"

#include "3dnow_arithmetic.h"
#include "3dnow_comparison.h"
#include "3dnow_conversion.h"
#include "3dnow_init.h"
#include "3dnow_transcendental.h"


struct {unsigned high, low;} tsc1, tsc2;

#define GET_TSC(X) __asm__(".byte 0x0f,0x31":"=a" (X.low), "=d" (X.high))

extern void mmx_regdump (mmx_t mmx_reg);


//	Function to test if mmx instructions are supported...

inline extern int
mmx_ok(void)
{
	/* Returns 1 if mmx instructions are ok,
	   0 if hardware does not support mmx
	*/
	register int ok = 0;

	__asm__ __volatile__ (
		/* Get CPU version information */
		"movl $1, %%eax\n\t"
		"cpuid\n\t"
		"movl %%edx, %0"
		: "=a" (ok)
		: /* no input */
	);
	return((ok & 0x800000) == 0x800000);
}


/*	Empty MMX State
	(used to clean-up when going from mmx to float use
	 of the registers that are shared by both; note that
	 there is no float-to-mmx operation needed, because
	 only the float tag word info is corruptible)
*/

// #define	emms() __asm__ __volatile__ ("emms")

/* TUNE_ME: dump of mmx_register  */
extern void mmx_regdump (mmx_t mmx_reg)
{
short i;
        printf("64 bit reg: %016llx\n", mmx_reg.q);
        printf("Hi-Float: %f  Lo-Float: %f\n",mmx_reg.f[1] ,mmx_reg.f[0]);
        for (i=1; i>=0; i--) printf("d[%d]:%08x ", i, mmx_reg.d[i]);
        printf("\n");
        for (i=3; i>=0; i--) printf("w[%d]:%04x ", i, mmx_reg.uw[i]);
        printf("\n");
        for (i=7; i>=0; i--) printf("b[%d]:%02x ", i, mmx_reg.ub[i]);
        printf("\n\n");
}
