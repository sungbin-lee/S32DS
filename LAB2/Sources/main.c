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

//Select one of tow Mode and change value
#define LAB2 0
#define SYSTICK 1

#if SYSTICK
#define SYSTICK_CTRL		*(uint32_t *)0xE000E010
#define SYSTICK_LOAD		*(uint32_t *)0xE000E014
#define SYSTICK_CURRENT		*(uint32_t *)0xE000E018
#define SYSTICK_CALIB		*(uint32_t *)0xE000E01C

#define Systick_IRQn -1

#define COUNT_MASKING 0x00FFFFFF
#endif

  void delay(volatile int cycles){
  	while(cycles--);
  }



void StartTask01()
{
  	for(;;){
	#if SYSTICK

  	  		printf("TASK 1 \n");
  			vTaskDelay(1 / portTICK_PERIOD_MS);
			//delay(1000);
	#endif
	#if LAB2
			printf("\n");
			printf("task1: %lu \n", xTaskGetTickCount());
			//delay(4000000);
			delay(3405000);
			vTaskDelay(2000 / portTICK_PERIOD_MS);
	#endif
  	}
}

void StartTask02()
{
	uint32_t lastTime;
  	for(;;){
	#if SYSTICK

  			printf("TASK 2 \n");
  			vTaskDelay(1 / portTICK_PERIOD_MS);
			//delay(1000);
	#endif
	#if LAB2
			lastTime = xTaskGetTickCount();
			printf("\n");
			printf("task2: %lu \n", lastTime);
			//delay(4000000);
			delay(3405000);
			vTaskDelayUntil(&lastTime, 2000 / portTICK_PERIOD_MS);
	#endif
  }
}

void StartTask03()
{
  	for(;;){
	#if SYSTICK
  			vTaskDelay(1 / portTICK_PERIOD_MS);
			printf("TASK 3 \n");

			//delay(1000);
	#endif
	#if LAB2
			printf("\n");
			printf("task1: %lu \n", xTaskGetTickCount());
			//delay(4000000);
			delay(3405000);
			vTaskDelay(2000 / portTICK_PERIOD_MS);
	#endif
  	}
}

#if SYSTICK
  void SysTick_handler(void){
  	printf("Systick Handler \n");
  }
#endif

int main(void)
{
  /* Write your local variable definition here */

	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
							g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);

	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	xTaskCreate( StartTask01, "T1", STACK_SIZE, NULL, tsk_PRIORITY+2, NULL );
	xTaskCreate( StartTask02, "T2", STACK_SIZE, NULL, tsk_PRIORITY+2, NULL );
	//xTaskCreate( StartTask03, "T3", STACK_SIZE, NULL, tsk_PRIORITY+3, NULL );

#if SYSTICK
	SYSTICK_CTRL |= ( 1 << 2U | 1 << 1U | 1 << 0U );  //
	SYSTICK_LOAD = 0x00FFFFFFFF;
	//SYSTICK_LOAD = 0x00000FFFFF;

	//INT_SYS_InstallHandler(-1, SysTick_handler, (isr_t *)NULL);
#endif

	vTaskStartScheduler();

/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

    for(;;) {}

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












