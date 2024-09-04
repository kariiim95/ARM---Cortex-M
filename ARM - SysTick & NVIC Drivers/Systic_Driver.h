/*
 * Systic Driver_Main.h
 *
 *  Created on: Jul 26, 2024
 *      Author: ASUS
 */

#ifndef SYSTIC_DRIVER_H_
#define SYSTIC_DRIVER_H_

#include "std_types.h"

/*Pointer to ISR handler*/
//volatile void (*Ptr2Func) (void);



 /* Description: Handler for SysTick interrupt use to call the call-back function*/
/*void SysTick_Handler(void)
{
    while(1)
    {

    }
}*/



/*
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using interrupts. This function is used to setup the timer to generate periodic
 * interrupts every specified time in milliseconds
*/

void SysTick_Init(uint16 a_TimeInMilliSeconds);




/*
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using polling or busy-wait technique. The function should exit when the time is
 * elapsed and stops the timer at the end.
*/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);



/*
 * Description: Handler for SysTick interrupt use to call the call-back function
 */

void SysTick_Handler(void);


/*
 * Description: Function to setup the SysTick Timer call back to be executed in
 * SysTick Handler
 */

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));




/*
 * Description: Start/Resume the SysTick timer.
 */
void SysTick_Start(void);



/*
 * Description: Stop the SysTick timer
 */
void SysTick_Stop(void);


/*
 * Description: Function to De-initialize the SysTick Timer
 */

void SysTick_DeInit(void);




#endif /* SYSTIC_DRIVER_H_ */
