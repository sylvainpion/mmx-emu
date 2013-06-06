/* 
 * This Programm shows how to use the emulator functions
 * and does some mesuring and benchmarking stuff
 * Just place a GET_TSC(tsc1); before and a GET_TSC(tsc2);tickdump(co); after
 * the command/section you want to mesure. The result is given in cpu-ticks
 */

/* Standart stuff */
#include <stdio.h>
#include <unistd.h>

/* mmx-register defs */
#include "mmx_types.h"

void tick_dump(int cpu_ofs)
{
	int tsc_d;
//	printf ("Timing start:  0x%X:%X\n",tsc1.high,tsc1.low);
//	printf ("Timing end  :  0x%X:%X\n",tsc2.high,tsc2.low);
	tsc_d = tsc2.low-tsc1.low;
	printf ("Messung dauer:  %d Ticks\n",tsc_d-cpu_ofs);
}




inline int calc_cpu_ofs()
{
	GET_TSC(tsc1);
	asm("
	");
	GET_TSC(tsc2);
	return (tsc2.low-tsc1.low);
}	

inline int calc_cpu_speed()
{
	GET_TSC(tsc1);
	usleep(2000000);
	GET_TSC(tsc2);
	return (tsc2.low-tsc1.low)/2000000;
}	



int main()
{
	int co, tmp;
	mmx_t ma, mb;  //, mm0, mm1, *pm0, *pm1;	

	tmp = 0;    /* Change to 0 to check 3dn-commands */
	if (tmp) {  
		tmp = calc_cpu_speed();
		printf(" Calculating CPU-Speed....running at %d MHz\n", tmp);
		printf(" Calculating CPU-OFFSET...found : ");
		co = calc_cpu_ofs();
		printf(" %d\n",co);
		exit(0);
	}
	/* PFCMPEQ *****************************************************/
	ma.f[0] = 1;
	mb.f[0] = 2;
	ma.f[1] = 3;
	mb.f[1] = 4;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pfcmpeq( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);
	/* PFCMPGE *****************************************************/
	ma.f[0] = 1;
	mb.f[0] = 2;
	ma.f[1] = 3;
	mb.f[1] = 4;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pfcmpeq( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);
	/* PFCMPGT *****************************************************/
	ma.f[0] = 2;
	mb.f[0] = 2;
	ma.f[1] = 2;
	mb.f[1] = 3;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pfcmpgt( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);
	/* PF2ID *****************************************************/
	ma.f[0] = 1;
	mb.f[0] = 2;
	ma.f[1] = 3;
	mb.f[1] = 4;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pf2id( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);
	/* PI2FD *****************************************************/
	ma.d[0] = 1;
	ma.d[1] = 2;
	mb.d[0] = 3;
	mb.d[1] = 4;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pi2fd( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);

	ma.q = 0x3f80000200000000LL;
	mb.q = 0x4000000100000000LL;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pfcmpeq( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);
	ma.q = 0x3f80000200000000LL;
	mb.q = 0x4000000100000000LL;
	mmx_regdump(ma);
	mmx_regdump(mb);
	pfcmpgt( &ma, &mb);
	mmx_regdump(ma);
	mmx_regdump(mb);


	
	exit(0); /* Clean-up and exit nicely */
}
