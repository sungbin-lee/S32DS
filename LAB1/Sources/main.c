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
  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
#define STACK_SIZE 				((unsigned long)90)
#define tsk_PRIORITY			0U
#define TIMER_PERIOD_MS		( 500UL / portTICK_PERIOD_MS )


typedef void * TimerHandle_t;

  void delay(volatile int cycles){

  	while(cycles--);
  }

  void StartTask01()
  {
  	for(;;){
  		printf("TASK1\n");
  		//printf("task1 : %lu \n",xTaskGetTickCount());
  		vTaskDelay(1000 / portTICK_PERIOD_MS );
  	}
  }

  void StartTask02()
  {
  	for(;;){
  		printf("TASK2\n");
  		//printf("task2 : %lu \n",xTaskGetTickCount());
  		vTaskDelay(1000 / portTICK_PERIOD_MS );
  		}
  }

  void StartTask03()
  {
  	for(;;){
  		printf("TASK3\n");
  		//printf("task3 : %lu \n",xTaskGetTickCount());
  		delay(1200000);
  	}
  }

  void StartTask04()
  {
  	for(;;){
  		printf("TASK4\n");
  		//printf("task3 : %lu \n",xTaskGetTickCount());
  		delay(1200000);
  	}
  }


void ISR(void){

	PTE->PTOR = (1 << 22U);
	delay(1200000);
	//PINS_DRV_ClearPortIntFlagCmd(PORTC);
	PORTC->ISFR = (PORTC->ISFR | (1 << 24U));
}


int main(void)
 {
  /* Write your local variable definition here */

	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
							g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);

	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	//PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

	INT_SYS_InstallHandler(PORTC_IRQn, ISR, (isr_t *)NULL);
	INT_SYS_EnableIRQ(PORTC_IRQn);

	xTaskCreate( StartTask01, "T1", STACK_SIZE, NULL, tsk_PRIORITY+3, NULL );
	xTaskCreate( StartTask02, "T2", STACK_SIZE, NULL, tsk_PRIORITY+3, NULL );
	xTaskCreate( StartTask03, "T3", STACK_SIZE, NULL, tsk_PRIORITY+2, NULL );
	xTaskCreate( StartTask04, "T4", STACK_SIZE, NULL, tsk_PRIORITY+2, NULL );

	vTaskStartScheduler();

/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

    for(;;) {

    	//LED_ON
/*
  	  	PTE->PSOR = (1 << 21U);
*/

    	//SW
/*
    	if((PINS_DRV_ReadPins(PTC) & (1 << 12U)) == (1 << 12U))
    		PTE->PSOR = (1 << 21U);
    	else
    		PTE->PCOR = (1 << 21U);
*/

    	//BLINK
/*
    	delay(720000);
    	PINS_DRV_TogglePins(PTE, 1 << 21U);
*/

    	//PTE->PCOR = (1 << 22U);
    }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

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
