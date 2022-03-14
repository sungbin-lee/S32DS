/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

// NVIC Registers
#define NVIC_BASE	(0xE000E100)
#define NVIC_ISER1	*((volatile unsigned*)(NVIC_BASE + 0x4))
#define NVIC_ICPR1	*((volatile unsigned*)(NVIC_BASE + 0x184))
#define NVIC_IPR12	*((volatile unsigned*)(NVIC_BASE + 0x330))

// PCC Registers
#define PCC_BASE	(0X40065000)
#define PCC_LPIT	*((volatile unsigned*)(PCC_BASE + 0xDC))
#define PCC_PORTD	*((volatile unsigned*)(PCC_BASE + 0x130))

#define PCS_BITS	24
#define	CGC_BIT		30

// PORT Registers
#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR0	*((volatile unsigned*)(PORTD_BASE + 0x0))

#define MUX_BITS	8

// GPIO Registers
#define GPIOD_BASE	(0x400FF0C0)
#define GPIOD_PTOR	*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR	*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTD0		0

// LPIT Registers
#define LPIT_BASE	(0x40037000)
#define LPIT_MCR	*((volatile unsigned*)(LPIT_BASE + 0x8))
#define LPIT_MSR	*((volatile unsigned*)(LPIT_BASE + 0xC))
#define LPIT_MIER	*((volatile unsigned*)(LPIT_BASE + 0x10))
#define LPIT_TVAL0	*((volatile unsigned*)(LPIT_BASE + 0x20))
#define LPIT_TCTRL0	*((volatile unsigned*)(LPIT_BASE + 0x28))

#define M_CEN_BIT	0
#define TIF0_BIT	0
#define TIE0_BIT	0
#define MODE_BITS	2
#define T_EN_BIT	0


void PORT_init();
void SOSC_init_8MHz();
void SPLL_init_160MHz();
void NormalRUNmode_80MHz();
void NVIC_init_IRQs();
void LPIT0_init();

int main(void) {


	PORT_init();				/* Configure ports */
	SOSC_init_8MHz();			/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();			/* Initialize SPLL to 160MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();		/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	NVIC_init_IRQs();			/* Enable desired interrupts and priorities */
	LPIT0_init();				/* Initialize LPIT0 for 1 second timeout */

    for (;;) {

    }

    return 0;
}

void LPIT0_Ch0_IRQHandler(void)
{
	GPIOD_PTOR |= (1<<PTD0);	/* Toggle Blue LED */
	LPIT_MSR |= (1<<TIF0_BIT);	/* Clear LPIT0'S ISF BIT */
}

void NVIC_init_IRQs(void)
{
	NVIC_ICPR1 |= (1<<(LPIT0_Ch0_IRQn % 32));
	NVIC_ISER1 |= (1<<(LPIT0_Ch0_IRQn % 32));
	NVIC_IPR12 &= ~(255<<(LPIT0_Ch0_IRQn % 4));
	NVIC_IPR12 |= (10<<(LPIT0_Ch0_IRQn % 4));
}

void LPIT0_init(void)
{
	/* LPIT Clocking */


	PCC_LPIT &= ~((0b111)<<PCS_BITS);
	PCC_LPIT |= ((0b110)<<PCS_BITS);		/* Clock Src = 6 (SPLL2_DIV2_CLK) */
	PCC_LPIT |= (1<<CGC_BIT);				/* Enable clk to LPIT0 regs */

	/* LPIT Initialization */
	LPIT_MCR |= (1<<M_CEN_BIT);				/* M_CEN=1: enable module clk (allows writing other LPIT0 regs */

	LPIT_MIER |= (1<<TIE0_BIT);				/* TIE0=1: Timer Interrupt Enabled for Channel 0 */

	LPIT_TVAL0 = 40000000;					/* Chan 0 Timeout period: 40M clocks */

	LPIT_TCTRL0 &= ~((0b11)<<MODE_BITS);	/* MODE=0: 32 periodic counter mode */
	LPIT_TCTRL0 |= (1<<T_EN_BIT);			/* T_EN=1: Timer channel is enabled */

}

void PORT_init(void)
{

		/* Initialization for Blue LED */
	 	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT D */

		PORTD_PCR0 &= ~((0b111)<<MUX_BITS);		/* PORT D0: MUX = GPIO */
		PORTD_PCR0 |= (1<<MUX_BITS);

		GPIOD_PDDR |= (1<<PTD0);				/* Configure PORT D0 as GPIO output (LED on EVB) */												/* PORT D0: Data Direction = output */

}

void SOSC_init_8MHz(void)
{
	/*!
	 * SOSC Initialization (8 MHz):
	 * ===================================================
	 */
	SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1)|
				   SCG_SOSCDIV_SOSCDIV2(1);  	/* SOSCDIV1 & SOSCDIV2 =1: divide by 1 		*/
	SCG->SOSCCFG  =	SCG_SOSCCFG_RANGE(2)|		/* Range=2: Medium freq (SOSC betw 1MHz-8MHz) 	*/
					SCG_SOSCCFG_EREFS_MASK;		/* HGO=0:   Config xtal osc for low power 		*/
  	  	  	  	  	  	  	  	  	  	  	  	/* EREFS=1: Input is external XTAL 			*/

  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); 	/* Ensure SOSCCSR unlocked 							*/
  SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK; 		/* LK=0:          SOSCCSR can be written 				*/
												/* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled 		*/
												/* SOSCCM=0:      OSC CLK monitor disabled 			*/
												/* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
												/* SOSCLPEN=0:    Sys OSC disabled in VLP modes 		*/
												/* SOSCSTEN=0:    Sys OSC disabled in Stop modes 		*/
												/* SOSCEN=1:      Enable oscillator 					*/

while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));	/* Wait for sys OSC clk valid */
}

void SPLL_init_160MHz(void)
{
	/*!
	 * SPLL Initialization (160 MHz):
	 * ===================================================
	 */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 				*/
  SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK;  	/* SPLLEN=0: SPLL is disabled (default) 	*/

  SCG->SPLLDIV |= 	SCG_SPLLDIV_SPLLDIV1(2)|	/* SPLLDIV1 divide by 2 */
					SCG_SPLLDIV_SPLLDIV2(3);  	/* SPLLDIV2 divide by 4 */

  SCG->SPLLCFG = SCG_SPLLCFG_MULT(24);			/* PREDIV=0: Divide SOSC_CLK by 0+1=1 		*/
  	  	  	  	  	  	  	  	  	  	  		/* MULT=24:  Multiply sys pll by 4+24=40 	*/
										  		/* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz 	*/

  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 						*/
  SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK; 		/* LK=0:        SPLLCSR can be written 			*/
                             	 	 	 		/* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled 	*/
                             	 	 	 	 	/* SPLLCM=0:    SPLL CLK monitor disabled 			*/
                             	 	 	 	 	/* SPLLSTEN=0:  SPLL disabled in Stop modes 		*/
                             	 	 	 	 	/* SPLLEN=1:    Enable SPLL 						*/

  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz (void)
{
/*! Slow IRC is enabled with high range (8 MHz) in reset.
 *	Enable SIRCDIV2_CLK and SIRCDIV1_CLK, divide by 1 = 8MHz
 *  asynchronous clock source.
 * ==========================================
*/
	SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1)
				 | SCG_SIRCDIV_SIRCDIV2(1);

/*!
 *  Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL:
 *  ====================================================
 */
  SCG->RCCR=SCG_RCCR_SCS(6)      /* Select PLL as clock source 								*/
    |SCG_RCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz 		*/
    |SCG_RCCR_DIVBUS(0b01)       /* DIVBUS=1, div. by 2: bus clock = 40 MHz 					*/
    |SCG_RCCR_DIVSLOW(0b10);     /* DIVSLOW=2, div. by 2: SCG slow, flash clock= 26 2/3 MHz	*/

  while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}	/* Wait for sys clk src = SPLL */
}
