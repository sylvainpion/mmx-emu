/*
 * How to access the registers...
 */

#include <asm/sigcontext.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < 2*65536+1*256+1)
typedef struct sigcontext_struct sigcontext_t;
#else
typedef struct sigcontext sigcontext_t;
#endif

extern sigcontext_t * context;

// Adress of an ALU register.
#define REG_(reg) ((&(context->eax)) - (reg))

// Adress of an MMX register.
#define MMX_REG_ADR(reg) (&(context->fpstate->_st[reg]))

// Adress of an implicit register (used by Cyrix'EMMX).
#define IMPL_REG(R) MMX_REG_ADR((((struct _fpreg *) (R)) - MMX_REG_ADR(0)) ^ 1)
