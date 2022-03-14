/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

// PCC Registers
#define PCC_BASE	(0X40065000)
#define PCC_ADC0	*((volatile unsigned*)(PCC_BASE + 0xEC))
#define PCC_PORTB	*((volatile unsigned*)(PCC_BASE + 0x128))
#define PCC_PORTE	*((volatile unsigned*)(PCC_BASE + 0x134))

#define PCS_BITS	24
#define	CGC_BIT		30

// PORT Registers
#define PORTB_BASE	(0x4004A000)
#define PORTB_PCR12	*((volatile unsigned*)(PORTB_BASE + 0x30))
#define PORTB_PCR13	*((volatile unsigned*)(PORTB_BASE + 0x34))
#define PORTB_PCR14	*((volatile unsigned*)(PORTB_BASE + 0x38))
#define PORTB_PCR15	*((volatile unsigned*)(PORTB_BASE + 0x3C))
#define PORTB_PCR16	*((volatile unsigned*)(PORTB_BASE + 0x40))
#define PORTB_PCR17	*((volatile unsigned*)(PORTB_BASE + 0x44))

#define PORTE_BASE	(0x4004D000)
#define PORTE_PCR8	*((volatile unsigned*)(PORTE_BASE + 0x20))
#define PORTE_PCR9	*((volatile unsigned*)(PORTE_BASE + 0x24))

#define MUX_BITS	8

// GPIO Registers
#define GPIOB_BASE	(0x400FF040)
#define GPIOB_PSOR	*((volatile unsigned*)(GPIOB_BASE + 0x4))
#define GPIOB_PCOR	*((volatile unsigned*)(GPIOB_BASE + 0x8))
#define GPIOB_PDDR	*((volatile unsigned*)(GPIOB_BASE + 0x14))

#define GPIOE_BASE	(0x400FF100)
#define GPIOE_PSOR	*((volatile unsigned*)(GPIOE_BASE + 0x4))
#define GPIOE_PCOR	*((volatile unsigned*)(GPIOE_BASE + 0x8))
#define GPIOE_PDDR	*((volatile unsigned*)(GPIOE_BASE + 0x14))

#define PTB12		12
#define PTB13		13
#define PTB14		14
#define PTB15		15
#define PTB16		16
#define PTB17		17
#define PTE8		8
#define PTE9		9

// ADC0 Registers
#define ADC0_BASE	(0x4003B000)
#define ADC0_SC1A	*((volatile unsigned*)(ADC0_BASE + 0x0))
#define ADC0_CFG1	*((volatile unsigned*)(ADC0_BASE + 0x40))
#define ADC0_CFG2	*((volatile unsigned*)(ADC0_BASE + 0x44))
#define ADC0_RA		*((volatile unsigned*)(ADC0_BASE + 0x48))
#define ADC0_SC2	*((volatile unsigned*)(ADC0_BASE + 0x90))
#define ADC0_SC3	*((volatile unsigned*)(ADC0_BASE + 0x94))

#define ADCH_BITS 	0
#define COCO_BIT	7
#define MODE_BITS	2
#define ADIV_BITS	5
#define SMPLTS_BITS	0
#define ADTRG_BIT	6
#define ADC0_SE4	4





uint32_t read_adc_chx(void);

int main(void) {

	uint32_t adcResult=0;

	SOSC_init_8MHz();			/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();			/* Initialize SPLL to 160MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();		/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();				/* Configure ports */
	ADC0_init();				/* Initialize ADC0 resolution 12-bit */

    for (;;) {
    	adc_start();

    	adcResult = read_adc_chx();		/* Wait for conversion complete */
    									/* Get channel's conversion result */

    	if(adcResult > 3583)
    	{
    		GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    		GPIOE_PCOR |= (1<<PTE8) | (1<<PTE9);					/* Turn on Red LED */
    	}
    	else if(adcResult > 3071)
    	{
    		GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    		GPIOE_PCOR |= (1<<PTE8);
    		GPIOE_PSOR |= (1<<PTE9);
    	}
    	else if(adcResult > 2559)
    	{
    		GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    		GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else if(adcResult > 2047)
    	{
    		GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16);
    		GPIOB_PSOR |= (1<<PTB17);
    		GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else if(adcResult > 1535)
    	{
    	    GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15);
    	    GPIOB_PSOR |= (1<<PTB16) | (1<<PTB17);
    	    GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else if(adcResult > 1023)
    	{
    		GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14);
    		GPIOB_PSOR |= (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    		GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else if(adcResult > 511)
    	{
    	    GPIOB_PCOR |= (1<<PTB12) | (1<<PTB13);
    	    GPIOB_PSOR |= (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    	    GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else if(adcResult > 0)
    	{
    	    GPIOB_PCOR |= (1<<PTB12);
    	    GPIOB_PSOR |= (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    	    GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    	else
    	{
    	    GPIOB_PSOR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);
    	    GPIOE_PSOR |= (1<<PTE8) | (1<<PTE9);
    	}
    }

    return 0;
}

void PORT_init(void)
{
		/* Initialization for Blue LED */
	 	PCC_PORTB |= (1<<CGC_BIT);

		PORTB_PCR12 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR12 |= (1<<MUX_BITS);
		PORTB_PCR13 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR13 |= (1<<MUX_BITS);
		PORTB_PCR14 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR14 |= (1<<MUX_BITS);
		PORTB_PCR15 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR15 |= (1<<MUX_BITS);
		PORTB_PCR16 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR16 |= (1<<MUX_BITS);
		PORTB_PCR17 &= ~((0b111)<<MUX_BITS);
		PORTB_PCR17 |= (1<<MUX_BITS);

		GPIOB_PDDR |= (1<<PTB12) | (1<<PTB13) | (1<<PTB14) | (1<<PTB15) | (1<<PTB16) | (1<<PTB17);

		PCC_PORTE |= (1<<CGC_BIT);

		PORTE_PCR8 &= ~((0b111)<<MUX_BITS);
		PORTE_PCR8 |= (1<<MUX_BITS);
		PORTE_PCR9 &= ~((0b111)<<MUX_BITS);
		PORTE_PCR9 |= (1<<MUX_BITS);

		GPIOE_PDDR |= (1<<PTE8) | (1<<PTE9);
}

void ADC0_init()
{
	/* ADC0 Clocking */
	PCC_ADC0 &= ~(1<<CGC_BIT);				/* Disable clock to change PCS */
	PCC_ADC0 &= ~((0b111)<<PCS_BITS);		/* PCS=0b001: Select SOSCDIV2 */
	PCC_ADC0 |= ((0b001)<<PCS_BITS);
	PCC_ADC0 |= (1<<CGC_BIT);				/* Enable bus clock in ADC0 */

	/* ADC0 Initialization */
	ADC0_SC1A |= ((0b111111)<<ADCH_BITS);	/* ADCH=1F: Moudle is disabled for conversion */

	ADC0_CFG1 &= ~((0b11)<<ADIV_BITS);		/* The divide ratio is 1 */
	ADC0_CFG1 &= ~((0b11)<<MODE_BITS);		/* MODE=1: 12-bit conversion */
	ADC0_CFG1 |= ((0b01)<<MODE_BITS);

	ADC0_CFG2 &= ~(255<<SMPLTS_BITS);		/* SMPLTS=12(default): sample time is 13 ADC clks */
	ADC0_CFG2 |= (12<<SMPLTS_BITS);

	ADC0_SC2 &= ~(1<<ADTRG_BIT);			/* ADTRG=0: SW trigger */

}

void adc_start(void)
{
	ADC0_SC1A &= ~((0b111111)<<ADCH_BITS);	/* Clear prior ADCH bits */
	ADC0_SC1A |= (ADC0_SE4<<ADCH_BITS);	/* Initiate Conversion */

}

uint32_t read_adc_chx(void)
{
	while((ADC0_SC1A & (1<<COCO_BIT))==0){}		/* Wait for conversion complete */

	return ADC0_RA;								/* ADC0 conversion result */
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
