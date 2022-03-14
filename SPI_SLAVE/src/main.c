/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

// PCC Registers
#define PCC_BASE		(0x40065000)
#define PCC_PORTB		*((volatile unsigned*)(PCC_BASE + 0x128))
#define PCC_PORTD		*((volatile unsigned*)(PCC_BASE + 0x130))

#define CGC_BIT			30

// PORT Registers
#define PORTB_BASE		(0x4004A000)
#define PORTB_PCR14		*((volatile unsigned*)(PORTB_BASE + 0x38))
#define PORTB_PCR15		*((volatile unsigned*)(PORTB_BASE + 0x3C))
#define PORTB_PCR16		*((volatile unsigned*)(PORTB_BASE + 0x40))
#define PORTB_PCR17		*((volatile unsigned*)(PORTB_BASE + 0x44))

#define PORTD_BASE		(0x4004C000)
#define PORTD_PCR0		*((volatile unsigned*)(PORTD_BASE + 0x0))
#define PORTD_PCR1		*((volatile unsigned*)(PORTD_BASE + 0x4))

#define MUX_BITS		8

// GPIO Registers
#define GPIOD_BASE		(0x400FF0C0)
#define GPIOD_PSOR		*((volatile unsigned*)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR		*((volatile unsigned*)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR		*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR		*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTD0			0

int main(void) {

	uint8_t dummy = 0xFF;
	char receive;
	//int i = 0;
	SOSC_init_8MHz();        /* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();      /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();   /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 2 0 MHz flash */
	LPSPI1_init_slave();    /* Initialize LPSPI 1 as slave */
	PORT_init();             /* Configure ports */


	for (;;) {

		LPSPI1_transmit_8bits (dummy);
		receive = LPSPI1_receive_8bits();
		if(receive == 0x11)
			GPIOD_PTOR |= (1<<PTD0);

    }

    return 0;
}


void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTB14             | LPSPI1_SCK
	 * PTB15             | LPSPI1_SIN
	 * PTB16			 | LPSPI1_SOUT
	 * PTB17			 | LPSPI1_PCS3
	 */
		PCC_PORTB |= (1<<CGC_BIT);

		PORTB_PCR14 &= ~((0b111)<<MUX_BITS);	/* PORT B14: MUX = ALT3 (LPSPI1_SCK) */
		PORTB_PCR14 |= ((0b011)<<MUX_BITS);
		//PORTB_PCR15 &= ~((0b111)<<MUX_BITS);	/* PORT B15: MUX = ALT3 (LPSPI1_SIN) */
		//PORTB_PCR15 |= ((0b011)<<MUX_BITS);
		PORTB_PCR16 &= ~((0b111)<<MUX_BITS);	/* PORT B16: MUX = ALT3 (LPSPI1_SOUT) */
		PORTB_PCR16 |= ((0b011)<<MUX_BITS);
		PORTB_PCR17 &= ~((0b111)<<MUX_BITS);	/* PORT B17: MUX = ALT3 (LPSPI1_PCS3) */
		PORTB_PCR17 |= ((0b011)<<MUX_BITS);


		PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT D */

		PORTD_PCR1 &= ~((0b111)<<MUX_BITS);	/* PORT D1: MUX = ALT3 (LPSPI1_SIN) */
		PORTD_PCR1 |= ((0b011)<<MUX_BITS);

		PORTD_PCR0 &= ~((0b111)<<MUX_BITS);	/* PORT D0: MUX = GPIO */
		PORTD_PCR0 |= (1<<MUX_BITS);

		GPIOD_PDDR |= (1<<PTD0);
		GPIOD_PSOR |= (1<<PTD0);
}
