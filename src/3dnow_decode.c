/*
 * Decoding of 3DNow! suffixes.
 * Copyright  Sylvain Pion, 1998.
 */

#include "emu.h"
#include "decode.h"
#include "3dnow_arithmetic.h"
#include "3dnow_conversion.h"
#include "3dnow_transcendental.h"
#include "3dnow_comparison.h"

/* AMD 3DNow! extensions.  This is the array of imm8 suffixes (see 21928c.pdf).
 * 19 opcodes (femms and prefetch are in mmx_insn[]).
 * See http://www.amd.com/K6/k6docs/
 */
static const FUNC _3dnow_insn[192] = {
/* 0/8 ,  1/9  ,  2/a  ,  3/b  ,  4/c  ,  5/d  ,  6/e  ,  7/f  */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 0 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,pi2fd  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 1 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,pf2id  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 2 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 3 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 4 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 5 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 6 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 7 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  , /* 8 */
__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,pfmin  ,__BAD  ,pfrcp  ,pfrsqrt, /* 9 */
__BAD  ,pfcmpge,pfsub  ,__BAD  ,__BAD  ,__BAD  ,pfadd  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,pfmax  ,__BAD ,pfrcpit1,pfrsqit1,/* a */
__BAD  ,pfcmpgt,pfsubr ,__BAD  ,__BAD  ,__BAD  ,pfacc  ,__BAD  ,
__BAD  ,__BAD  ,__BAD  ,__BAD  ,pfmul  ,__BAD ,pfrcpit2,pmulhrw_3dnow, /* b */
__BAD  ,pfcmpeq,__BAD  ,__BAD  ,__BAD  ,__BAD  ,__BAD  ,pavgusb,
/* 0/8 ,  1/9  ,  2/a  ,  3/b  ,  4/c  ,  5/d  ,  6/e  ,  7/f  */
};

unsigned char _3dnow_suffix;
void _3dnow(void *src, void *dest)
{
        _3dnow_insn[_3dnow_suffix](src,dest);
        mmx_printf("3dnow insn called\n");
}
