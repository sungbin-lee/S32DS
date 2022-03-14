/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

// PCC Registers
#define PCC_BASE	(0X40065000)
#define PCC_ADC0	*((volatile unsigned*)(PCC_BASE + 0xEC))
#define PCC_PORTD	*((volatile unsigned*)(PCC_BASE + 0x130))

#define PCS_BITS	24
#define	CGC_BIT		30

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
#define ADC0_SE12	12

// PORT Registers
#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR0	*((volatile unsigned*)(PORTD_BASE + 0x0))
#define PORTD_PCR15	*((volatile unsigned*)(PORTD_BASE + 0x3C))
#define PORTD_PCR16	*((volatile unsigned*)(PORTD_BASE + 0x40))

#define MUX_BITS	8

// GPIO Registers
#define GPIOD_BASE	(0x400FF0C0)
#define GPIOD_PSOR	*((volatile unsigned*)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR	*((volatile unsigned*)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR	*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR	*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTD0		0
#define PTD15		15
#define PTD16		16

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

    	if(adcResult > 3072)
    	{
    		GPIOD_PSOR |= ((1<<PTD0) | (1<<PTD16));		/* Turn off Blue, Green LEDs */
    		GPIOD_PCOR |= (1<<PTD15);					/* Turn on Red LED */
    	}
    	else if(adcResult > 2048)
    	{
    		GPIOD_PSOR |= ((1<<PTD0) | (1<<PTD15));		/* Turn off Blue, Red LEDs */
    		GPIOD_PCOR |= (1<<PTD16);					/* Turn on Green LED */
    	}
    	else if(adcResult > 1024)
    	{
    	    GPIOD_PSOR |= ((1<<PTD15) | (1<<PTD16));	/* Turn off Red, Red LEDs */
    	    GPIOD_PCOR |= (1<<PTD0);					/* Turn on Blue LED */
    	}
    	else
    	{
    		GPIOD_PSOR |= ((1<<PTD0) | (1<<PTD15) | (1<<PTD16));	/* Turn off all LEDs */
    	}

    }

    return 0;
}

void PORT_init(void)
{
		/* Initialization for Blue LED */
	 	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
												/* Enable clock to PORT D */

		PORTD_PCR0 &= ~((0b111)<<MUX_BITS);		/* PORT D0: MUX = GPIO */
		PORTD_PCR0 |= (1<<MUX_BITS);
		PORTD_PCR15 &= ~((0b111)<<MUX_BITS);	/* PORT D15: MUX = GPIO */
		PORTD_PCR15 |= (1<<MUX_BITS);
		PORTD_PCR16 &= ~((0b111)<<MUX_BITS);	/* PORT D16: MUX = GPIO */
		PORTD_PCR16 |= (1<<MUX_BITS);

		GPIOD_PDDR |= (1<<PTD0)				/* Configure PORT D0  (Blue LED) 	*/
					  |(1<<PTD15)			/* Configure PORT D15 (Red LED) 	*/
					  |(1<<PTD16);			/* Configure PORT D16 (Green LED)	*/
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
	ADC0_SC1A |= (ADC0_SE12<<ADCH_BITS);	/* Initiate Conversion */

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
