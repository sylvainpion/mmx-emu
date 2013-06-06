
typedef void (*FUNC)(void *, void *);

#ifdef MMX_DEBUG
#define mmx_printf(a) printf(a)
#else
#define mmx_printf(a) /* */
#endif

extern void MMX_illegal(void *, void *);
extern void emms(void *, void *);
extern void movq2mem(void *, void *);
extern void movd2mem(void *, void *);
extern void movq2mmx(void *, void *);
extern void movd2mmx(void *, void *);
