/*
 * Systic Driver_Main.c
 *
 *  Created on: Jul 26, 2024
 *      Author: ASUS
 */

#include <Systic_Driver.h>
#include "tm4c123gh6pm_registers.h"


static volatile void (*g_CallBackPtr) (void) = NULL_PTR;


void SysticTick_Handler(void)
{
    if (g_CallBackPtr != NULL_PTR)
    {
        (*g_CallBackPtr) ();
    }
}


/*
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using interrupts. This function is used to setup the timer to generate periodic
 * interrupts every specified time in milliseconds
*/

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{

    SYSTICK_CTRL_REG    = 0;      /* Disable the SysTick Timer by Clear the ENABLE Bit */

    SYSTICK_RELOAD_REG  = (a_TimeInMilliSeconds * 16000)-1 ;    /* Set the Reload value with 15999999 to count 1 Second */
    SYSTICK_CURRENT_REG = 0;      /* Clear the Current Register value */
   /*  Configure the SysTick Control Register
        * Enable the SysTick Timer (ENABLE = 1)
        * Enable SysTick Interrupt (INTEN = 1)
        * Choose the clock source to be System Clock (CLK_SRC = 1) */
     SYSTICK_CTRL_REG   |= 0x07;
      while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */
      //SYSTICK_CTRL_REG    = 0;      /* Disable the SysTick Timer by Clear the ENABLE Bit */

}


/*
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using polling or busy-wait technique. The function should exit when the time is
 * elapsed and stops the timer at the end.
*/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;      /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = (a_TimeInMilliSeconds * 16000)-1 ; /* Set the Reload value with 15999999 to count 1 Second */
    SYSTICK_CURRENT_REG = 0;      /* Clear the Current Register value */

       /* Configure the SysTick Control Register
           * Enable the SysTick Timer (ENABLE = 1)
           * Disable SysTick Interrupt (INTEN = 0)
           * Choose the clock source to be System Clock (CLK_SRC = 1) */
          SYSTICK_CTRL_REG   |= 0x05;
          while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */
          SYSTICK_CTRL_REG    = 0;      /* Disable the SysTick Timer by Clear the ENABLE Bit */

}

/*
 * Description: Function to setup the SysTick Timer call back to be executed in
 * SysTick Handler
 */

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_CallBackPtr=Ptr2Func;

}


/*
 * Description: Start/Resume the SysTick timer.
 */
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |= (1<<0);

}



/*
 * Description: Stop the SysTick timer
 */
void SysTick_Stop(void)
{
  //  SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
   // SYSTICK_RELOAD_REG  = 0x00;           /* Clear Reload value */
    SYSTICK_CTRL_REG &= ~(1<<0);

}


/*
 * Description: Function to De-initialize the SysTick Timer
 */

void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG    = 0x00;   /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_CURRENT_REG = 0x000000;          /* Clear the Current Register value */
    SYSTICK_RELOAD_REG  = 0x000000;         /* Clear Reload value */
}

