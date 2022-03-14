/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K1xx
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"
#include <stdio.h>

#define SYSTICK_CTRL		*(uint32_t *)0xE000E010
#define SYSTICK_LOAD		*(uint32_t *)0xE000E014
#define SYSTICK_CURRENT		*(uint32_t *)0xE000E018
#define SYSTICK_CALIB		*(uint32_t *)0xE000E01C

#define Systick_IRQn -1

#define COUNT_MASKING 0x00FFFFFF



  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

  unsigned int sys_msec = 0;



void SysTick_handler(void){
	//printf("Systick Handler \n");
	PTE->PTOR = (1 << 16u);
}

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/




int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
    							g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);

    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);


    SYSTICK_CTRL |= ( 1 << 2U | 1 << 1U | 1 << 0U );  //
	SYSTICK_LOAD = 60000;

	INT_SYS_InstallHandler(-1, SysTick_handler, (isr_t *)NULL);


    for(;;){
    	//printf("CURRENT : %lu \n", SYSTICK_CURRENT & COUNT_MASKING);
    }

  return exit_code;
}

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP S32K series of microcontrollers.
**
** ###################################################################
*/
