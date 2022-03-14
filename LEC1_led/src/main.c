/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

//	PCC Registers
#define PCC_BASE	(0x40065000)
#define PCC_PORTD	*((volatile unsigned*)(PCC_BASE + 0x130))

#define CGC_BIT		30

//	PORTD Registers
#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR0	*((volatile unsigned*)(PORTD_BASE + 0x0))

#define MUX_BITS	8

//	GPIOD Registers
#define GPIOD_BASE	(0x400FF0C0)
#define GPIOD_PTOR	*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR	*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTD0		0


int main(void) {

	/* Enable clocks to peripherals (PORT modules) */
	/* Enable clock to PORT D */
 	PCC_PORTD |= (1<<CGC_BIT);

	/* PORT D0: MUX = GPIO */
	PORTD_PCR0 &= ~((0b111)<<MUX_BITS);
	PORTD_PCR0 |= (1<<MUX_BITS);

	/* Configure PORT D0 as GPIO output (LED on EVB) */
	/* PORT D0: Data Direction = output */
	GPIOD_PDDR |= (1<<PTD0);

    for (;;) {

    	int cycles = 720000;
    	while(cycles--);
    	GPIOD_PTOR |= (1<<PTD0);

    }
}
