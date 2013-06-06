typedef void (*FUNC)(void *, void *);

extern FUNC mmx_insn[256];
void __BAD(void *, void *);
int mmx_decode(void);
