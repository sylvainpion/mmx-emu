/* 
 * This Programm shows how to use the emulator functions
 * and does some mesuring and benchmarking stuff
 * Just place a GET_TSC(tsc1); before and a GET_TSC(tsc2);tickdump(co); after
 * the command/section you want to mesure. The result is given in cpu-ticks
 */

/* Standart stuff */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* mmx-register defs */
#include "mmx_types.h"

void tick_dump(int cpu_ofs)
{
	int tsc_d;
//	printf ("Messung start:  0x%X:%X\n",tsc1.high,tsc1.low);
//	printf ("Messung end  :  0x%X:%X\n",tsc2.high,tsc2.low);
	tsc_d = tsc2.low-tsc1.low;
	printf ("Messung dauer:  %d Ticks\n",tsc_d-cpu_ofs);
}




inline int calc_cpu_ofs()
{
	GET_TSC(tsc1);
	asm("
//	nop\n
	");
	GET_TSC(tsc2);
	return (tsc2.low-tsc1.low);
}	

inline int calc_cpu_speed()
{
	GET_TSC(tsc1);
	usleep(2500000);
	GET_TSC(tsc2);
	return (tsc2.low-tsc1.low)/2500000;
}	



int main()
{
	int rval, i, co, tmp;   //, j;
	mmx_t ma, mb;  //, mm0, mm1, *pm0, *pm1;	

	tmp = calc_cpu_speed();
	printf(" Calculating CPU-Speed....running at %d MHz\n", tmp);
	printf(" Calculating CPU-OFFSET...found : ");
	co = calc_cpu_ofs();
	printf(" %d\n",co);
	rval = 1; //mmx_ok(); /* Announce return value of mmx_ok() */
	printf(" *** Bogus message since we are emulating so MMX does allways exist ***\n");
	printf(" Value returned from init was %x.", rval);
	printf(" (Indicates MMX %s available)\n\n",(rval)? "is" : "not");
	
	if(rval) {
		/* PADD *****************************************************/
		ma.q = 0x1111111180000000LL;
		mb.q = 0x7fffffff00000001LL;
		mmx_regdump(ma);
		mmx_regdump(mb);
		paddd( &ma, &mb);		 
		printf("paddd: mb.q is %016llx\n", mb.q);
		mmx_regdump(mb);
		paddw( &ma, &mb);
		mmx_regdump(ma);
		mmx_regdump(mb);  
		ma.q = 0x0000000000000008LL;
		mb.q = 0x0001000200030004LL;
		mmx_regdump(ma);
		mmx_regdump(mb);
		psllw( &ma, &mb);
		mmx_regdump(ma);
		mmx_regdump(mb); 
		ma.q = 0x0000000000000000LL;
		mb.q = 0x888044a87f06fe80LL;
		mmx_regdump(ma);
		mmx_regdump(mb);
//		packuswb( &ma,&mb);
		ma.q = 0x00aa00dd01009999LL;
		mb.q = 0x0011002200330044LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		packuswb( &ma, &mb); 
//		punpckhdq(&ma,&mb);
		mmx_regdump(ma);		
		mmx_regdump(mb);
/* punpckhdq */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpckhdq( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);		
/* punpckhwd */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpckhwd( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);	
/* punpckhbw */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpckhbw( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);	

/* punpckldq */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpckldq( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);		
/* punpcklwd */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpcklwd( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);	
/* punpcklbw */
		ma.q = 0x090a0b0c0d0e0f00LL;
		mb.q = 0x0102030405060708LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		punpcklbw( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);	

/* pmaddwd */
		ma.q = 0x8000800080008000LL;
		mb.q = 0x8000800080008000LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		pmaddwd( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);
/* packsswb */
		ma.q = 0x00aa00dd01009999LL;
		mb.q = 0x0011002200330044LL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		packsswb( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);
/* packsswb */
		ma.q = 0x007e7f00ef9dff88LL;
		mb.q = 0xff020085007e81cfLL;
		mmx_regdump(ma);		
		mmx_regdump(mb);
		packsswb( &ma, &mb); 
		mmx_regdump(ma);		
		mmx_regdump(mb);		
		for (i=0; i< 0x0F; i++){
			printf ("%d. Test running\n", i);
			GET_TSC(tsc1);
			mb.w[0] = i;
			ma.w[0] = i;
			GET_TSC(tsc2);
			tick_dump(co);
			GET_TSC(tsc1);     /* Let's test some real asm */
			asm("
//			pushl %eax\n
//			movl $0, %eax\n
//			cpuid\n
			packsswb %mm0, %mm1\n
			pmaddwd %mm0, %mm1\n
			punpcklbw %mm0, %mm1\n
			punpcklbw %mm0, %mm1\n
			pmaddwd %mm0, %mm1\n
			punpcklbw %mm0, %mm1\n
//			popl %eax\n
			");
			GET_TSC(tsc2);
			tick_dump(co);
			ma.q = 0x8000800080008000LL;
			mb.q = 0x8000800080008000LL;
			GET_TSC(tsc1);     /* Here some emulated routines */
			pmaddwd( &ma, &mb);
//			packsswb( &ma, &mb);
			GET_TSC(tsc2);
			tick_dump(co);
//			mmx_regdump(mb);
		}

		}
	exit(0); /* Clean-up and exit nicely */
}
