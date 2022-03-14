/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
//#include "S32K144.h"
#include "clocks_and_modes.h"

#define PCC_BASE	(0x40065000)
#define PCC_PORTC	*((volatile unsigned*)(PCC_BASE + 0x12C))
#define PCC_LPUART1	*((volatile unsigned*)(PCC_BASE + 0x1AC))

#define CGC_BIT		30
#define PCS_BITS	24

#define LPUART1_BASE	(0x4006B000)
#define LPUART1_BAUD	*((volatile unsigned*)(LPUART1_BASE + 0x10))
#define LPUART1_STAT	*((volatile unsigned*)(LPUART1_BASE + 0x14))
#define LPUART1_CTRL	*((volatile unsigned*)(LPUART1_BASE + 0x18))
#define LPUART1_DATA	*((volatile unsigned*)(LPUART1_BASE + 0x1C))

#define M10_BIT		29
#define OSR_BITS	24
#define SBNS_BIT	13
#define SBR_BITS	0
#define TDRE_BIT	23
#define RDRF_BIT	21
#define TE_BIT		19
#define RE_BIT		18
#define M7_BIT		11
#define M_BIT		4
#define PE_BIT		1

#define PORTC_BASE	(0x4004B000)
#define PORTC_PCR6	*((volatile unsigned*)(PORTC_BASE + 0x18))
#define PORTC_PCR7	*((volatile unsigned*)(PORTC_BASE + 0x1C))

#define MUX_BITS	8

int main(void) {

	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz ();
	PORT_init();
	LPUART1_init();

	LPUART1_transmit_string("Running LPUART example \n\r");

	for(;;)
	{
			char receive;
			receive = LPUART1_receive_char();


	}

    return 0;
}

void LPUART1_transmit_char(char send){
	while((LPUART1_STAT & (1 << TDRE_BIT)) == 0);

	LPUART1_DATA = send;
}

void LPUART1_transmit_string(char data_string[]){
	uint32_t i = 0;
	while(data_string[i] != '\0'){
		LPUART1_transmit_char(data_string[i]);
		i++;
	}
}

char LPUART1_receive_char(void){
	char receive;
	while((LPUART1_STAT & (1<<RDRF_BIT)) == 0 );

	receive = LPUART1_DATA;
	return receive;
}

void LPUART1_init(void)
{
	PCC_LPUART1 &= ~(1 << CGC_BIT);
	PCC_LPUART1 &= ~((0b111) << PCS_BITS);
	PCC_LPUART1 |= ((0b010) << PCS_BITS);
	PCC_LPUART1 |= (1 << CGC_BIT);

	LPUART1_BAUD &= ~(1 << M10_BIT);
	LPUART1_BAUD &= ~(1 << SBNS_BIT);

	LPUART1_BAUD &= ~((0b11111) << OSR_BITS);
	LPUART1_BAUD |= (15 << OSR_BITS);
	LPUART1_BAUD &= ~(8191  << SBR_BITS);
	LPUART1_BAUD |= (52 << SBR_BITS);

	LPUART1_CTRL &= ~(1 << M7_BIT);
	LPUART1_CTRL &= ~(1 << M_BIT);
	LPUART1_CTRL &= ~(1 << PE_BIT);

	LPUART1_CTRL |= (1 << TE_BIT);
	LPUART1_CTRL |= (1 << RE_BIT);


}
