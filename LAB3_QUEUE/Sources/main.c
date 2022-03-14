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
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"


/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( 1 )

/* The rate at which data is sent to the queue, specified in milliseconds, and
converted to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( 200 / portTICK_PERIOD_MS )

/* A block time of zero simply means "don't block". */
#define mainDONT_BLOCK						( 0UL )

#define mainQUEUE_LENGTH					( 5 )

volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

static void prvQueueReceiveTask();
static void prvQueueSendTask();

void delay(volatile int cycles)
 {
     /* Delay function - do nothing for a number of cycles */
     while(cycles--);
 }

  /* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;


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


	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );



	xTaskCreate( prvQueueReceiveTask, "RX", configMINIMAL_STACK_SIZE+90, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL );
	xTaskCreate( prvQueueSendTask, "TX", configMINIMAL_STACK_SIZE+90, NULL, mainQUEUE_SEND_TASK_PRIORITY, NULL );

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

static void prvQueueSendTask()
{
unsigned long ulValueToSend = 0UL;
int temp = ulValueToSend;

	for( ;; )
	{
		ulValueToSend = temp++;
		printf("send : %lu\n", ulValueToSend);

		//xQueueSend( xQueue, &ulValueToSend, mainDONT_BLOCK );
		xQueueSend( xQueue, &ulValueToSend, portMAX_DELAY );
	}
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask()
{
unsigned long ulReceivedValue;
	for( ;; )
	{
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );
		printf("receive : %lu\n", ulReceivedValue);
		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
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
