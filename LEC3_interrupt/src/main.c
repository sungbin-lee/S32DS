/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

//	PCC Registers
#define PCC_BASE		(0x40065000)
#define PCC_PORTC		*((volatile unsigned*)(PCC_BASE + 0x12C))
#define PCC_PORTD		*((volatile unsigned*)(PCC_BASE + 0x130))

#define CGC_BIT			30

//	PORT Registers
#define PORTC_BASE		(0x4004B000)
#define PORTC_PCR12		*((volatile unsigned*)(PORTC_BASE + 0x30))

#define PORTD_BASE		(0x4004C000)
#define PORTD_PCR0		*((volatile unsigned*)(PORTD_BASE + 0x0))

#define MUX_BITS		8
#define IRQC_BITS		16
#define ISF_BIT			24

//	GPIO Registers
#define GPIOC_BASE		(0x400FF080)
#define GPIOC_PDIR		*((volatile unsigned*)(GPIOC_BASE + 0x10))
#define GPIOC_PDDR		*((volatile unsigned*)(GPIOC_BASE + 0x14))

#define GPIOD_BASE		(0x400FF0C0)
#define GPIOD_PSOR		*((volatile unsigned*)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR		*((volatile unsigned*)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR		*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR		*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTC12			12
#define PTD0			0

//NVIC Regisers
#define NVIC_ISER_BASE	(0xE000E100)
#define NVIC_ISER1		*((volatile unsigned*)(NVIC_ISER_BASE + 0x4))

#define NVIC_ICPR_BASE	(0xE000E280)
#define NVIC_ICPR1		*((volatile unsigned*)(NVIC_ICPR_BASE + 0x4))

#define NVIC_IPR_BASE	(0xE000E400)
#define NVIC_IPR61		*((volatile unsigned char*)(NVIC_IPR_BASE + 0x3D))



void PORT_init(void);
void NVIC_init_IRQs(void);
void PORTC_IRQHandler(void);

int main(void) {

	PORT_init();
	NVIC_init_IRQs();

    for (;;) {

    }
}

void PORT_init(void)
{
	/*initialization for Switch2 */
		PCC_PORTC |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT C */

		PORTC_PCR12 &= ~((0b111)<<MUX_BITS);	/* PORT C12: MUX = GPIO */
		PORTC_PCR12 |= (0b001<<MUX_BITS);

		GPIOC_PDDR &= ~(1<<PTC12);				/* Configure PORT C12 as GPIO output (Switch2 on EVB) */
												/* PORT C12: Data Direction = input */

		PORTC_PCR12 &= ~((0b1111)<<IRQC_BITS);	/* PORT C12 IRQC: Interrupt on rising-edge */
		PORTC_PCR12 |= ((0b1001)<<IRQC_BITS);

		/* Initialization for Blue LED */
	 	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT D */

		PORTD_PCR0 &= ~((0b111)<<MUX_BITS);		/* PORT D0: MUX = GPIO */
		PORTD_PCR0 |= (1<<MUX_BITS);

		GPIOD_PDDR |= (1<<PTD0);				/* Configure PORT D0 as GPIO output (LED on EVB) */												/* PORT D0: Data Direction = output */

}

void NVIC_init_IRQs(void)
{
	//NVIC_ICPR1 |= (1<<(PORTC_IRQn % 32));
	NVIC_ISER1 |= (1<<(PORTC_IRQn % 32));
	//NVIC_IPR61 = 10;
}

void PORTC_IRQHandler(void)
{
	GPIOD_PTOR |= (1<<PTD0);
	PORTC_PCR12 |= (1<<ISF_BIT);
}
