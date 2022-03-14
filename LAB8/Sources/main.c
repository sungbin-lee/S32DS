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

#include "timers.h"


  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

  /*
   * The LED timer callback function.  This does nothing but switch off the
   * LED defined by the mainTIMER_CONTROLLED_LED constant.
   */
  static void prvTimerCallback( TimerHandle_t xTimer );

  /* The LED software timer.  This uses prvButtonLEDTimerCallback() as its callback
  function. */
  static TimerHandle_t xTimer = NULL;


/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
  /* Write your local variable definition here */

	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
	                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

    //xTaskCreate( Task1, "T1", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL );

    xTimer = xTimerCreate( 				"LEDTimer", 			/* A text name, purely to help debugging. */
    									500UL / portTICK_PERIOD_MS,	/* The timer period, in this case 500ms (0.5s). */
    									pdTRUE,						/* pdTRUE -> Auto-reload,  pdFALSE -> One-shot */
    									( void * ) 0,					/* The ID is not used, so can be set to anything. */
    									prvTimerCallback		/* The callback function that switches the LED off. */
    								);

    xTimerStart( xTimer, 500UL / portTICK_PERIOD_MS);
    vTaskStartScheduler();


  /* Write your code here */
  /* For example: for(;;) { } */

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


/*-----------------------------------------------------------*/

static void prvTimerCallback( TimerHandle_t xTimer )
{
	/* Casting xTimer to void because it is unused */
	(void)xTimer;

	PINS_DRV_TogglePins(PTE, (1 << 21U));
}
/*-----------------------------------------------------------*/




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
