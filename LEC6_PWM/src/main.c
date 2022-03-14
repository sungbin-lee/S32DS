/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

// PCC Registers
#define PCC_BASE	(0X40065000)
#define PCC_FTM0	*((volatile unsigned*)(PCC_BASE + 0xE0))
#define PCC_PORTD	*((volatile unsigned*)(PCC_BASE + 0x130))

#define PCS_BITS	24
#define	CGC_BIT		30

// PORT Registers
#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR16	*((volatile unsigned*)(PORTD_BASE + 0x40))

#define MUX_BITS	8

// FTM0 Registers
#define FTM0_BASE	(0x40038000)
#define FTM0_SC		*((volatile unsigned*)(FTM0_BASE + 0x0))
#define FTM0_MOD	*((volatile unsigned*)(FTM0_BASE + 0x8))
#define FTM0_C1SC	*((volatile unsigned*)(FTM0_BASE + 0x14))
#define FTM0_C1V	*((volatile unsigned*)(FTM0_BASE + 0x18))
#define FTM0_CNTIN	*((volatile unsigned*)(FTM0_BASE + 0x4C))

#define PWMEN1_BIT	17
#define CLKS_BITS	3
#define	PS_BITS		0
#define MSB_BIT		5
#define MSA_BIT		4
#define ELSB_BIT	3
#define ELSA_BIT	2

int main(void) {

	SOSC_init_8MHz();			/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();			/* Initialize SPLL to 160MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();		/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	PORT_init();				/* Configure ports */
	FTM0_CH1_PWM();				/* Initialize ADC0 resolution 12-bit */

    for (;;) {

    }

    return 0;
}

void FTM0_CH1_PWM(void)
{
	/* FTM0 Clocking */
	PCC_FTM0 &= ~(1<<CGC_BIT);				/* Ensure clk disabled for config */
	PCC_FTM0 &= ~((0b111)<<PCS_BITS);		/* Clock Src=1, 8 MHz SIRCDIV1_CLK */
	PCC_FTM0 |= ((0b010)<<PCS_BITS);
	PCC_FTM0 |= (1<<CGC_BIT);				/* Enable clock for FTM regs */

	/* FTM0 Initialization */
	FTM0_SC |= (1<<PWMEN1_BIT);				/* Enable PWM channel 1 output */
	FTM0_SC &= ~((0b111)<<PS_BITS);			/* PS (Prescaler factor) = 1, Prescaler = 2 */
	FTM0_SC |= ((0b001)<<PS_BITS);			/* 8MHz /  2 = 4MHz */

	FTM0_MOD = 16000 - 1;					/* FTM0 counter final value (used for PWM mode) */
	FTM0_CNTIN = 0;							/* FTM0 Period = MOD - CNTIN + 0x0001 ~= 16000 ctr clks = 8ms */

	/* FTM0, Channel 1 in PWM mode */
	FTM0_C1SC |= (1 << MSB_BIT);			/* FTM0 ch1: edge-aligned PWM, low true pulses */
	FTM0_C1SC |= (1<<ELSA_BIT);				/* MSB:MSA (chan Mode Select) = 0b1x, Edge Aligned PWM */
											/* ELSB:ELSA (chan Edge/Level Select) = 0bx1, low true */
	FTM0_C1V = 4095;

	/* Start FTM0 counter with clk source = external clock (SIRCDIV1_CLK) */
	FTM0_SC |= ((0b11)<<CLKS_BITS);
}

void PORT_init(void)
{
		/* Initialization for Blue LED */
	 	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT D */

		PORTD_PCR16 &= ~((0b111)<<MUX_BITS);	/* PORT D16: MUX = Alternative2 (FTM0_CH1) */
		PORTD_PCR16 |= ((0b010)<<MUX_BITS);

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
