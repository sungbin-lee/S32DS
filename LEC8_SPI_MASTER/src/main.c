/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include <stdint.h>
#include "clocks_and_modes.h"

//#define MASTER
#define SLAVE

// PCC Registers
#define PCC_BASE		(0x40065000)
#define PCC_LPSPI1		*((volatile unsigned*)(PCC_BASE + 0xB4))
#define PCC_PORTB		*((volatile unsigned*)(PCC_BASE + 0x128))
#define PCC_PORTD		*((volatile unsigned*)(PCC_BASE + 0x130))

#define CGC_BIT			30
#define PCS_BITS		24

// LPSPI1 Registers
#define LPSPI1_BASE		(0x4002D000)
#define LPSPI1_CR		*((volatile unsigned*)(LPSPI1_BASE + 0x10))
#define LPSPI1_SR		*((volatile unsigned*)(LPSPI1_BASE + 0x14))
#define LPSPI1_CFGR1	*((volatile unsigned*)(LPSPI1_BASE + 0x24))
#define LPSPI1_CCR		*((volatile unsigned*)(LPSPI1_BASE + 0x40))
#define LPSPI1_FCR		*((volatile unsigned*)(LPSPI1_BASE + 0x58))
#define LPSPI1_TCR		*((volatile unsigned*)(LPSPI1_BASE + 0x60))
#define LPSPI1_TDR		*((volatile unsigned*)(LPSPI1_BASE + 0x64))
#define LPSPI1_RDR		*((volatile unsigned*)(LPSPI1_BASE + 0x74))

#define MASTER_BIT		0
#define CPOL_BIT		31
#define CPHA_BIT		30
#define PRESCALE_BITS	27
#define PCS_BITS		24
#define FRAMESZ_BITS	0
#define SCKPCS_BITS		24
#define PCSSCK_BITS		16
#define DBT_BITS		8
#define SCKDIV_BITS		0
#define TXWATER_BITS	0
#define MEN_BIT			0
#define DBGEN_BIT		3
#define TDF_BIT			0
#define RDF_BIT			1

// PORT Registers
#define PORTB_BASE		(0x4004A000)
#define PORTB_PCR14		*((volatile unsigned*)(PORTB_BASE + 0x38))
#define PORTB_PCR15		*((volatile unsigned*)(PORTB_BASE + 0x3C))
#define PORTB_PCR16		*((volatile unsigned*)(PORTB_BASE + 0x40))
#define PORTB_PCR17		*((volatile unsigned*)(PORTB_BASE + 0x44))

#define PORTD_BASE	(0x4004C000)
#define PORTD_PCR0	*((volatile unsigned*)(PORTD_BASE + 0x0))
#define PORTD_PCR1	*((volatile unsigned*)(PORTD_BASE + 0x4))

#define MUX_BITS		8

// GPIO Registers
#define GPIOD_BASE		(0x400FF0C0)
#define GPIOD_PSOR		*((volatile unsigned*)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR		*((volatile unsigned*)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR		*((volatile unsigned*)(GPIOD_BASE + 0xC))
#define GPIOD_PDDR		*((volatile unsigned*)(GPIOD_BASE + 0x14))

#define PTD0			0

/* Function Prototype */
void LPSPI1_init(void);
void LPSPI1_transmit_8bits(uint8_t send);
uint8_t LPSPI1_receive_8bits(void);
void PORT_init (void);

uint8_t master_to_slave = 0x11;
uint8_t slave_to_master = 0x00;
uint8_t receive = 0;

int main(void) {

	SOSC_init_8MHz ();			/* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz ();		/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz ();		/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	LPSPI1_init();				/* Init LPSPI1 */
	PORT_init();				/* Configure ports */

    for (;;) {
#ifdef MASTER
    		LPSPI1_transmit_8bits(master_to_slave);
    		LPSPI1_receive_8bits();

    		int delay = 720000;
    		while(delay--);

#endif
#ifdef SLAVE
    		LPSPI1_transmit_8bits(slave_to_master);
    		receive = LPSPI1_receive_8bits();
    		if(receive == master_to_slave)
    			GPIOD_PTOR = (1<<PTD0);
    		receive = 0;
#endif
    }
    return 0;
}

void LPSPI1_init(void)
{
	/*!
		 * LPSPI1 Clocking:
		 * ===================================================
		 */

		PCC_LPSPI1 = 0;          		/* Disable clocks to modify PCS ( default) 	*/
		PCC_LPSPI1 = (1<<CGC_BIT)		/* Enable PCS=SPLL_DIV2 (40 MHz func'l clock) 	*/
					|((0b110)<<PCS_BITS);
		/*!
		 * LPSPI1 Initialization:
		 * ===================================================
		 */
	  LPSPI1_CR = 0;   							/* Disable module for configuration 			*/

#ifdef MASTER
	  LPSPI1_CFGR1 = (1<<MASTER_BIT);  			/* Configurations: master mode									*/
												/* PCSCFG=0: PCS[3:2] are enabled 								*/
												/* OUTCFG=0: Output data retains last value when CS negated		*/
												/* PINCFG=0: SIN is input, SOUT is output 						*/
												/* MATCFG=0: Match disabled 									*/
												/* PCSPOL=0: PCS is active low 									*/
												/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
												/* AUTOPCS=0: does not apply for master mode 					*/
												/* SAMPLE=0: input data sampled on SCK edge 					*/
												/* MASTER=1: Master mode 										*/
#endif
#ifdef SLAVE
	  LPSPI1_CFGR1 = 0;  						/* Configurations: slave mode									*/
												/* PCSCFG=0: PCS[3:2] are enabled 								*/
												/* OUTCFG=0: Output data retains last value when CS negated	*/
												/* PINCFG=0: SIN is input, SOUT is output 						*/
												/* MATCFG=0: Match disabled 									*/
												/* PCSPOL=0: PCS is active low 								*/
												/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
												/* AUTOPCS=0: does not apply for master mode 					*/
												/* SAMPLE=0: input data sampled on SCK edge 					*/
												/* MASTER=0: Slave mode 										*/
#endif

	  LPSPI1_TCR = (1<<CPHA_BIT)
					  |((0b010)<<PRESCALE_BITS)
					  |((0b11)<<PCS_BITS)
					  |((0b000000000111)<<FRAMESZ_BITS);   /* Transmit cmd: PCS3, 16 bits, prescale func'l clk by 4, etc	*/
															/* CPOL=0: SCK inactive state is low 							*/
															/* CPHA=1: Change data on SCK lead'g, capture on trail'g edge	*/
															/* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
															/* PCS=3: Transfer using PCS3 									*/
															/* LSBF=0: Data is transfered MSB first 						*/
															/* BYSW=0: Byte swap disabled 									*/
															/* CONT, CONTC=0: Continuous transfer disabled 					*/
															/* RXMSK=0: Normal transfer: rx data stored in rx FIFO 			*/
															/* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
															/* WIDTH=0: Single bit transfer 								*/
															/* FRAMESZ=15: # bits in frame = 15+1=16 						*/

	  LPSPI1_CCR = ((0b00000100)<<SCKPCS_BITS)
					  |((0b00000100)<<PCSSCK_BITS)
					  |((0b00001000)<<DBT_BITS)
					  |((0b00001000)<<SCKDIV_BITS);   	/* Clock dividers based on prescaled func'l clk of 100 nsec 	*/
														/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) 				*/
														/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 				*/
														/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 			*/
														/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) 	*/

	  LPSPI1_FCR = ((0b11)<<TXWATER_BITS);   	/* RXWATER=0: Rx flags set when Rx FIFO >0 		*/
	                                			/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	*/

	  LPSPI1_CR = (1<<MEN_BIT)
			  	  	  |(1<<DBGEN_BIT);   		/* Enable module for operation 				*/
												/* DBGEN=1: module enabled in debug mode 	*/
												/* DOZEN=0: module enabled in Doze mode 	*/
												/* RST=0: Master logic not reset 			*/
												/* MEN=1: Module is enabled 				*/
}

void LPSPI1_transmit_8bits(uint8_t send)
{
	while((LPSPI1_SR & (1<<TDF_BIT))>>TDF_BIT == 0);	/* Wait for Tx FIFO available 	*/

	LPSPI1_TDR = send;				/* Transmit data 				*/
	LPSPI1_SR |= (1<<TDF_BIT); 		/* Clear TDF flag 				*/
}

uint8_t LPSPI1_receive_8bits (void)
{
  uint8_t recieve = 0;

  while((LPSPI1_SR & (1<<RDF_BIT))>>RDF_BIT == 0);
                           	   	   						/* Wait at least one RxFIFO entry 	*/
  recieve= LPSPI1_RDR;           						/* Read received data 				*/
  LPSPI1_SR |= (1<<RDF_BIT);							/* Clear RDF flag 					*/
  return recieve;            							/* Return received data 			*/
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
	PORTB_PCR15 &= ~((0b111)<<MUX_BITS);	/* PORT B15: MUX = ALT3 (LPSPI1_SIN) */
	PORTB_PCR15 |= ((0b011)<<MUX_BITS);
	PORTB_PCR16 &= ~((0b111)<<MUX_BITS);	/* PORT B16: MUX = ALT3 (LPSPI1_SOUT) */
	PORTB_PCR16 |= ((0b011)<<MUX_BITS);
	PORTB_PCR17 &= ~((0b111)<<MUX_BITS);	/* PORT B17: MUX = ALT3 (LPSPI1_PCS3) */
	PORTB_PCR17 |= ((0b011)<<MUX_BITS);


#ifdef SLAVE
	PCC_PORTD |= (1<<CGC_BIT);				/* Enable clocks to peripherals (PORT modules) */
											/* Enable clock to PORT D */

	PORTD_PCR0 &= ~((0b111)<<MUX_BITS);		/* PORT D0: MUX = GPIO  */
	PORTD_PCR0 |= (1<<MUX_BITS);

	GPIOD_PDDR |= (1<<PTD0);				/* D0 output */
#endif

}
