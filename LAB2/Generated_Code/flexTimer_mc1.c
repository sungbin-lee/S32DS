/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : flexTimer_mc1.c
**     Project     : LAB2
**     Processor   : S32K148_176
**     Component   : ftm_mc
**     Version     : Component SDK_S32K1xx_15, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K1xx_15
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-06-04, 15:13, # CodeGen: 4
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
** @file flexTimer_mc1.c
** @version 01.00
*/         
/*!
**  @addtogroup flexTimer_mc1_module flexTimer_mc1 module documentation
**  @{
*/         

/* Module flexTimer_mc1.
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, external symbol defined without a prior
 * declaration.
 * The symbols are declared in the driver header as external; the header is not included 
 * by this file.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variable will be used in other source files in application code.
 */

#include "flexTimer_mc1.h"



/* Timer mode configuration for flexTimer_mc1 */
ftm_timer_param_t flexTimer_mc1_TimerConfig =
{
    FTM_MODE_UP_TIMER, /* Counter mode */
    0U, /* Initial counter value */
    65535U, /* Final counter value */
};

/* Global configuration of flexTimer_mc1 */
ftm_user_config_t  flexTimer_mc1_InitConfig =
{
    {
        true,   /* Software trigger state */
        false,  /* Hardware trigger 1 state */
        false,  /* Hardware trigger 2 state */
        false,  /* Hardware trigger 3 state */
        false, /* Max loading point state */
        false, /* Min loading point state */
        FTM_SYSTEM_CLOCK, /* Update mode for INVCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for SWOCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for OUTMASK register */
        FTM_SYSTEM_CLOCK, /* Update mode for CNTIN register */
        false, /* Automatic clear of the trigger*/
        FTM_UPDATE_NOW, /* Synchronization point */
    },
     FTM_MODE_UP_TIMER, /* Mode of operation for FTM */
     FTM_CLOCK_DIVID_BY_1, /* FTM clock prescaler */
     FTM_CLOCK_SOURCE_SYSTEMCLK,   /* FTM clock source */
     FTM_BDM_MODE_00, /* FTM debug mode */
     false, /* Interrupt state */
     false /* Initialization trigger */
};

/* END flexTimer_mc1. */

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

