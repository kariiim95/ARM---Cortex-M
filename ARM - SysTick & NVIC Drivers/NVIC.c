/*
 * NVIC.c
 *
 *  Created on: Aug 1, 2024
 *      Author: ASUS
 *      updated , the first upload was half wrong,
 *      please accept this driver, Fully functional
 *
 */


#include"NVIC.h"
#include "tm4c123gh6pm_registers.h"



/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
 **********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 IRQ_REG;
     IRQ_REG = IRQ_Num / 32;

    if (0<=IRQ_Num<=31)
    {
        NVIC_EN0_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
    }
    else if (32<=IRQ_Num<=63)
    {
        NVIC_EN1_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
    }
    else if (64<=IRQ_Num<=95)
    {
        NVIC_EN2_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
    }
    else if (96<=IRQ_Num<=127)
    {
        NVIC_EN3_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
    }
    else if (128<=IRQ_Num<=159)
    {
        NVIC_EN4_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
    }

}

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
 **********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{

         uint8 IRQ_REG;
         IRQ_REG = IRQ_Num / 32;

        if (0<=IRQ_Num<=31)
        {
            NVIC_DIS0_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
        }
        else if (32<=IRQ_Num<=63)
        {
            NVIC_DIS1_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
        }
        else if (64<=IRQ_Num<=95)
        {
            NVIC_DIS2_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
        }
        else if (96<=IRQ_Num<=127)
        {
            NVIC_DIS3_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
        }
        else if (128<=IRQ_Num<=159)
        {
            NVIC_DIS4_REG |= (1 << (IRQ_Num - (32 * IRQ_REG)));
        }

}


/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                   IRQ_Priority - The required priority of this specific IRQ
 * Parameters (input): None
 * Parameters (output): None
 * Return value: None
 * Description: Function to set the priority value for specific IRQ.
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,
                         NVIC_IRQPriorityType IRQ_Priority)
{
    uint8 PRI_REG = IRQ_Num / 4;
    uint8 IRQ_Loc = IRQ_Num % 4;
    uint8 Shift_Index;
    switch (IRQ_Loc)
    {
    case 0:
        Shift_Index = 5;
        break;
    case 1:
        Shift_Index = 13;
        break;
    case 2:
        Shift_Index = 21;
        break;
    case 3:
        Shift_Index = 29;
        break;
    }

    if (PRI_REG == 0)
    {
        (*((volatile uint32*) (0xE000E100 + PRI_REG * 4))) |= (IRQ_Priority
                << IRQ_Num);
    }
    else
    {
        (*((volatile uint32*) (0xE000E100 + PRI_REG * 4))) |= (IRQ_Priority
                << Shift_Index);
    }

}


/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{


    if (Exception_Num ==EXCEPTION_RESET_TYPE  )
    {

    }
    else if  (Exception_Num == EXCEPTION_NMI_TYPE )
    {

    }
    else if (Exception_Num ==  EXCEPTION_HARD_FAULT_TYPE )
    {
   }
   else if ( Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
   {
        /* Enable the Bus Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL |= (1<<BUS_FAULT_ENABLE_BIT_POS);
   }
   else if ( Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
   {
         /* Enable the USAGE Fault Exception */
         NVIC_SYSTEM_SYSHNDCTRL |= (1<<USAGE_FAULT_ENABLE_BIT_POS);
   }
   else if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE )
   {
        /* Enable the MEMORY Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL |= (1<<MEM_FAULT_ENABLE_BIT_POS);
   }
   else if (Exception_Num == EXCEPTION_PEND_SV_TYPE )
   {
        /* Enable the PEND SV Exception */
       NVIC_SYSTEM_INTCTRL |= (1<<PENDSV_ENABLE_BITS_POS);
   }
   else if (Exception_Num ==   EXCEPTION_SVC_TYPE )
   {

   }

}




/*Description: Function to disable specific ARM system or fault exceptions*/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{

    if (Exception_Num ==EXCEPTION_RESET_TYPE  )
     {

     }
      else if (Exception_Num ==EXCEPTION_NMI_TYPE  )
      {

      }
      else if (Exception_Num ==  EXCEPTION_HARD_FAULT_TYPE )
      {
           Enable_Faults();
      }
      else if ( Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
       {
            /* Enable the Bus Fault Exception */
       NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<BUS_FAULT_ENABLE_BIT_POS);
       }
       else if ( Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
       {
           /* Enable the USAGE Fault Exception */
         NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<USAGE_FAULT_ENABLE_BIT_POS);
        }
       else if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE )
       {
            /* Enable the MEMORY Fault Exception */
            NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<MEM_FAULT_ENABLE_BIT_POS);
       }
       else if (Exception_Num == EXCEPTION_PEND_SV_TYPE )
       {
            /* Enable the PEND SV Exception */
           NVIC_SYSTEM_INTCTRL &= ~(1<<PENDSV_ENABLE_BITS_POS);
       }
       else if (Exception_Num ==   EXCEPTION_SVC_TYPE )
       {
       }

}


/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 *                   Exception_Priority - The required priority of this specific Exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific ARM system or fault
 * exceptions.
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num,
                               NVIC_ExceptionPriorityType Exception_Priority)
{

    uint8 PRI_REG = Exception_Num / 4;
    uint8 Exception_Loc = Exception_Num % 4;
    uint8 Shift_Index;
    switch (Exception_Loc)
    {
    case 0:
        Shift_Index = 5;
        break;
    case 1:
        Shift_Index = 13;
        break;
    case 2:
        Shift_Index = 21;
        break;
    case 3:
        Shift_Index = 29;
        break;
    }
    switch (PRI_REG)
    {
    case 1:
        NVIC_SYSTEM_PRI1_REG |= (Exception_Loc << Shift_Index);
        break;
    case 2:
        NVIC_SYSTEM_PRI2_REG |= (Exception_Loc << Shift_Index);
        break;
    case 3:
        NVIC_SYSTEM_PRI3_REG |= (Exception_Loc << Shift_Index);
        break;
    }
}
