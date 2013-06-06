/* 
 * This Programm does some mesuring and benchmarking stuff
 * Just place a GET_TSC(tsc1); before and a GET_TSC(tsc2);tickdump(co); after
 * the command/section you want to mesure. The result is given in cpu-ticks
 */

/* Standart stuff */
#include <stdio.h>
#include <unistd.h>

struct {unsigned high, low} tsc1, tsc2;

#define GET_TSC(X) __asm__(".byte 0x0f,0x31":"=a" (X.low), "=d" (X.high))


void tick_dump(int cpu_ofs)
{
	int tsc_d;
//	printf ("Startvalue:  0x%X:%X\n",tsc1.high,tsc1.low);
//	printf ("Endvalue  :  0x%X:%X\n",tsc2.high,tsc2.low);
	tsc_d = tsc2.low-tsc1.low;
	printf ("Duration  :  %d Ticks\n",tsc_d-cpu_ofs);
}



/* 
   We need to calculate the duration of measure to get an offset
   which is beeing substrated from the total duration,
   unfortunately the offset depends of the CPU, remove the 
   asm/(NOP)-stuff if it eats to much CPU-time ;-)
*/
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
	int co, tmp;

	tmp = calc_cpu_speed();
	printf(" Calculating CPU-Speed....running at %d MHz\n", tmp);
	printf(" Calculating CPU-OFFSET...found : ");
	co = calc_cpu_ofs();
	printf(" %d\n",co);
	exit(0); /* Clean-up and exit nicely */
}
