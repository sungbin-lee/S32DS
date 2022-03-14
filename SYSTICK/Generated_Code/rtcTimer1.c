/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : rtcTimer1.c
**     Project     : SYSTICK
**     Processor   : S32K148_176
**     Component   : rtc
**     Version     : Component SDK_S32K1xx_15, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K1xx_15
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-06-30, 12:50, # CodeGen: 0
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc. 
**     Copyright 2016-2017 NXP 
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file rtcTimer1.c
** @version 01.00
*/         
/*!
**  @addtogroup rtcTimer1_module rtcTimer1 module documentation
**  @{
*/         

/*! MODULE rtcTimer1. */

#include "rtcTimer1.h"

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, global macro not referenced
 * There are global macros defined to be used by the integrator and another one used as include guard.
 */





/*! rtcTimer1 configuration structure */
rtc_init_config_t rtcTimer1_Config0 =
{
    /*! Time compensation interval */
    .compensationInterval       =   0U,
    /*! Time compensation value */
    .compensation               =   0,
    /*! RTC Clock Source is 1KHz LPO */
    .clockSelect                =   RTC_CLK_SRC_LPO_1KHZ,
    /*! RTC Clock Out is disabled */
    .clockOutConfig             =   RTC_CLKOUT_DISABLED,
    /*! Update of the TCE bit is not allowed */
    .updateEnable               =   false,
    /*! Non-supervisor mode write accesses are not supported and generate
     * a bus error.
     */
    .nonSupervisorAccessEnable  =   false
};


/*! rtcTimer1 Initial Time and Date */
rtc_timedate_t rtcTimer1_StartTime0 =
{
    /*! Year */
    .year       =   2016U,
    /*! Month */
    .month      =   1U,
    /*! Day */
    .day        =   1U,
    /*! Hour */
    .hour       =   0U,
    /*! Minutes */
    .minutes    =   0U,
    /*! Seconds */
    .seconds    =   0U
};

/*! rtcTimer1 Register lock configuration 0 */
rtc_register_lock_config_t rtcTimer1_LockConfig0 =
{
    /*! Do not change the lock state of the Lock Register */
    .lockRegisterLock               =   false,
    /*! Do not change the lock state of the Status Register */
    .statusRegisterLock             =   false,
    /*! Do not change the lock state of the Control Register */
    .controlRegisterLock            =   false,
    /*! Do not change the lock state of the Time Compensation Register */
    .timeCompensationRegisterLock   =   false
};

/*! rtcTimer1 Fault Interrupt configuration (Time Overflow Interrupt & Time Invalid Interrupt) 0 */
rtc_interrupt_config_t rtcTimer1_FaultIntConfig0 =
{
    /*! Time Overflow Interrupt is disabled */
    .overflowIntEnable      =   false,
    /*! Time Invalid Interrupt is disabled */
    .timeInvalidIntEnable   =   false,
    /*! General User Callback */
    .rtcCallback            =   NULL,
    /*! General User Callback Parameters */
    .callbackParams         =   NULL
};

/*! rtcTimer1 Time Seconds Interrupt Configuration 0 */
rtc_seconds_int_config_t rtcTimer1_SecIntConfig0 =
{
    /*! Time Seconds Interrupt Frequency @ 2 Hz */
    .secondIntConfig               =    RTC_INT_2HZ,
    /*! Time Seconds Interrupt is disabled */
    .secondIntEnable               =    false,
    /*! Time Seconds Interrupt User Callback */
    .rtcSecondsCallback            =    NULL,
    /*! Time Seconds Interrupt User Callback Parameters */
    .secondsCallbackParams         =    NULL
};

/*! rtcTimer1 Alarm configuration 0 */
rtc_alarm_config_t rtcTimer1_AlarmConfig0 =
{
    /*! Alarm Date */
    .alarmTime           =
        {
            /*! Year    */
            .year       =   2016U,
            /*! Month   */
            .month      =   1U,
            /*! Day     */
            .day        =   1U,
            /*! Hour    */
            .hour       =   0U,
            /*! Minutes */
            .minutes    =   0U,
            /*! Seconds */
            .seconds    =   0U,
        },
    /*! Alarm repeat interval */
    .repetitionInterval  =      0UL,
    /*! Number of alarm repeats */
    .numberOfRepeats     =      0UL,
    /*! Repeat alarm disabled */
    .repeatForever       =      false,
    /*! Alarm interrupt disabled */
    .alarmIntEnable      =      false,
    /*! Alarm interrupt User Callback */
    .alarmCallback       =      NULL,
    /*! Alarm interrupt User Callback parameters */
    .callbackParams      =      NULL
};

/*! END rtcTimer1. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/

