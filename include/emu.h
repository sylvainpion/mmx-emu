#ifdef MMX_DEBUG
#include <stdio.h>
#define mmx_printf(args...) printf(## args)
#else
#define mmx_printf(args...) /* */
#endif
