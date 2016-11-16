/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_LDD.h
**     Project     : ProcessorExpert
**     Processor   : MKL46Z256VMC4
**     Version     : Component 01.002, Driver 01.04, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-11-16, 15:22, # CodeGen: 23
**     Abstract    :
**
**     Settings    :
**
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file PE_LDD.h                                                  
** @version 01.04
** @brief
**
*/         
/*!
**  @addtogroup PE_LDD_module PE_LDD module documentation
**  @{
*/         
#ifndef __PE_LDD_H
#define __PE_LDD_H

/* MODULE PE_LDD. */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "S0_Rodilla.h"
#include "BitIoLdd1.h"
#include "S1_Rodilla.h"
#include "BitIoLdd2.h"
#include "PWM_Rodilla.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM_Cadera_Flexion.h"
#include "PwmLdd2.h"
#include "PWM_Cadera_Aduccion.h"
#include "PwmLdd3.h"
#include "PWM_Tobillo.h"
#include "PwmLdd4.h"
#include "TU2.h"
#include "S0_Cadera_Aduccion.h"
#include "BitIoLdd3.h"
#include "S1_Cadera_Aduccion.h"
#include "BitIoLdd4.h"
#include "S0_Cadera_Flexion.h"
#include "BitIoLdd5.h"
#include "S1_Cadera_Flexion.h"
#include "BitIoLdd6.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU3.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "DA1.h"


/*
** ===================================================================
** Function prototypes
** ===================================================================
*/

/*
** ===================================================================
**     Method      :  Cpu_PE_FillMemory (component MKL46Z256MC4)
*/
/*!
**     @brief
**         Fills a memory area block by a specified value.
**     @param
**       SourceAddressPtr - Source address pointer.
**     @param
**       c - A value used to fill a memory block.
**     @param
**       len - Length of a memory block to fill.
*/
/* ===================================================================*/
void PE_FillMemory(register void* SourceAddressPtr, register uint8_t c, register uint32_t len);

/*
** ===================================================================
**     Method      :  Cpu_PE_PeripheralUsed (component MKL46Z256MC4)
*/
/*!
**     @brief
**         Returns information whether a peripheral is allocated by PEx 
**         or not.
**     @param
**       PrphBaseAddress - Base address of a peripheral.
**     @return
**       TRUE if a peripheral is used by PEx or FALSE if it isn't used.
*/
/* ===================================================================*/
bool PE_PeripheralUsed(uint32_t PrphBaseAddress);

/*
** ===================================================================
**     Method      :  Cpu_LDD_SetClockConfiguration (component MKL46Z256MC4)
*/
/*!
**     @brief
**         Changes the clock configuration of all LDD components in a 
**         project.
**     @param
**       ClockConfiguration - New CPU clock configuration changed by CPU SetClockConfiguration method.
*/
/* ===================================================================*/
void LDD_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration);

/* END PE_LDD. */


#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
