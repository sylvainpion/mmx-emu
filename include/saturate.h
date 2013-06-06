/*
 * Different saturatation definitions (used by arithmetic & cyrix).
 * (C) <Vincent.Renardias@waw.com>, 1998, LGPL.
 */

#define saturatenone(a)	(a)

#define SATURATE(TYPE, SIGN, VALUE_MAX, VALUE_MIN)			\
static inline TYPE saturate##TYPE##SIGN (int a)				\
{									\
	if (a>(int)(SIGN TYPE)VALUE_MAX) return (TYPE) VALUE_MAX;	\
	if (a<(int)(SIGN TYPE)VALUE_MIN) return (TYPE) VALUE_MIN;	\
	return (TYPE) a;						\
}

SATURATE(char,    signed, 0x7F,   0x80)
SATURATE(char,  unsigned, 0xFF,   0x0)
SATURATE(short,   signed, 0x7FFF, 0x8000)
SATURATE(short, unsigned, 0xFFFF, 0x0)

/* Fake saturations for PMUL* instructions */

static inline short saturatelow  (int a)   { return (short) (a&0x0000FFFF); }
static inline short saturatehigh (int a)   { return (short) (a>>16); }
