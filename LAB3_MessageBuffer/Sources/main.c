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

#include "stream_buffer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"

#define mainQUEUE_RECEIVE_TASK_PRIORITY		( 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( 1 )


  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

  static void SendTask();
  static void ReceiveTask();

  StreamBufferHandle_t xStreamBuffer;
  const size_t xStreamBufferSizeBytes = 100, xTriggerLevel = 10;

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


  xStreamBuffer = xStreamBufferCreate(xStreamBufferSizeBytes, xTriggerLevel);

  if(xStreamBuffer == NULL)
  {
	  printf(" There is no Storage size in Heap Memory \n");
	  exit(1);
  }


  xTaskCreate( ReceiveTask, "RX", configMINIMAL_STACK_SIZE+90, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL );
  xTaskCreate( SendTask, "TX", configMINIMAL_STACK_SIZE+90, NULL, mainQUEUE_SEND_TASK_PRIORITY, NULL );

  vTaskStartScheduler();

  /* Write your code here */
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


static void SendTask()
{
size_t xBytesSent;
uint8_t ucArrayToSend[] =  {0, 1, 2, 3};
char *pcStringToSend = "보낼 문자열";
const TickType_t x100ms = pdMS_TO_TICKS(100);


	//for( ;; )
	//{
		// 배열을 스트림 버퍼로 보내고 최대 100ms 동안 차단
		// 스트림 버퍼에서 사용 가능한 공간이 충분할 때까지 기다림
		xBytesSent = xStreamBufferSend(xStreamBufferSizeBytes, ucArrayToSend, sizeof(ucArrayToSend), x100ms);

		if(xBytesSent != sizeof(ucArrayToSend))
		{
			printf("times out before there was enough space in the buffer");
		}

		//문자열을 스트림 버퍼로 보냄
		//버퍼에 충분한 공간이 없는 경우 즉시 반품
		xBytesSent = xStreamBufferSend(xStreamBufferSizeBytes, pcStringToSend, sizeof(pcStringToSend), 0);

		if(xBHytesSent != strlen(pcStringToSend))
		{
			printf("Can't append String to Stream Buffer, because there was no free space in the buffer ");
		}

	//}
}
/*-----------------------------------------------------------*/

static void ReceiveTask()
{
uint8_t ucRxData[20];
size_t xReceivedBytes;
const TickType_t xBlockTime = pdMS_TO_TICKS(20);

	//for( ;; )
	//{
		xReceivedBytes = xStreamBufferReceive(xStreamBufferSizeBytes, ucRxData, sizeof(ucRxData), xBlockTime);
	//}

		if(xReceivedBytes > 0)
		{
			printf("ucRxData contains another xReceivedBytes of data");
		}
		else
		{
			printf(" data : %d %d %d %d ", ucRxData[0], ucRxData[1], ucRxData[2], ucRxData[3]);
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
