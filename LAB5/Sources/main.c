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

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"


volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

static void StartTask1();
static void StartTask2();

void delay(volatile int cycles)
 {
     /* Delay function - do nothing for a number of cycles */
     while(cycles--);
 }


SemaphoreHandle_t xSemaphore = NULL;


/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
  /* Write your local variable definition here */
/*
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
	                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
*/
	xSemaphore = xSemaphoreCreateBinary ();

	    if (xSemaphore == NULL)
	    {
	        printf(" Fail to create Semaphore!\n");
	    }
	    else
	    {
	        printf("Success create Semaphore!\n");
	    }


	xTaskCreate( StartTask1, "T1", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( StartTask2, "T2", configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	vTaskStartScheduler();

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  for(;;) { }

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


static void StartTask1()
{
	for( ;; )
	{
		vTaskDelay( 2000 / portTICK_PERIOD_MS);
		printf("Task1 release semaphore. \n");
		xSemaphoreGive(xSemaphore);
	}
}

static void StartTask2()
{
	int32_t retVal;
	for( ;; )
	{
		retVal = xSemaphoreTake(xSemaphore, 1000 / portTICK_PERIOD_MS);
		if(retVal == pdTRUE)
		{
			printf("Task2 syncronized!\n");
		}
		else
		{
			printf("Task2 timeout or error!\n");
		}
	}
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
