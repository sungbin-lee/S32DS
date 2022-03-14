/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

//	PCC Registers
#define PCC_BASE	(0x40065000)
#define PCC_PORTC	*((volatile unsigned*)(PCC_BASE + 0x12C))
#define PCC_PORTD	*((volatile unsigned*)(PCC_BASE + 0x130))

#define CGC_BIT		30

//	PORT Registers
#define PORTC_BASE	(0x4004B000)
#define PORTC_PCR12	*((volatile unsigned*)(PORTC_BASE + 0x30))

#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR0	*((volatile unsigned*)(PORTD_BASE + 0x0))

#define MUX_BITS	8

//	GPIO Registers
#define GPIOC_BASE	(0x400FF080)
#define GPIOC_PDIR	*((volatile unsigned*)(GPIOC_BASE + 0x10))
#define GPIOC_PDDR	*((volatile unsigned*)(GPIOC_BASE + 0x14))

#define GPIOD_BASE	(0x400FF0C0)
#define GPIOD_PSOR	*((volatile unsigned*)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR	*((volatile unsigned*)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR	*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR	*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTC12		12
#define PTD0		0



int main(void) {

	/*initialization for Switch2 */
	PCC_PORTC |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
											/* Enable clock to PORT C */

	PORTC_PCR12 &= ~((0b111)<<MUX_BITS);	/* PORT D0: MUX = GPIO */
	PORTC_PCR12 |= (1<<MUX_BITS);

	GPIOC_PDDR &= ~(1<<PTC12);				/* Configure PORT C12 as GPIO output (Switch2 on EVB) */
											/* PORT C12: Data Direction = input */

	/* Initialization for Blue LED */
 	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
											/* Enable clock to PORT D */

	PORTD_PCR0 &= ~((0b111)<<MUX_BITS);		/* PORT D0: MUX = GPIO */
	PORTD_PCR0 |= (1<<MUX_BITS);

	GPIOD_PDDR |= (1<<PTD0);				/* Configure PORT D0 as GPIO output (LED on EVB) */
											/* PORT D0: Data Direction = output */


    for (;;) {

    	if(GPIOC_PDIR & (1<<PTC12))			/* if switch2 was pushed -> PDIR == 0, if switch2 was not pushed -> PDIR == 1 */
    	{
    		GPIOD_PCOR |= (1<<PTD0);		/* if Switch2 was not pushed , LED off */
    	}
    	else
    	{
    		GPIOD_PSOR |= (1<<PTD0);		/* if Switch2 was pushed , LED on */
    	}

    }
}
