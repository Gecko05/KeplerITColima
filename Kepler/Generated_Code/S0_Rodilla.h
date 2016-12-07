/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : S0_Rodilla.h
**     Project     : ProcessorExpert
**     Processor   : MKL46Z256VMC4
**     Component   : BitIO
**     Version     : Component 02.086, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-11-14, 12:44, # CodeGen: 7
**     Abstract    :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings    :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       74            |  LCD_P21/ADC0_SE15/TSI0_CH14/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0/I2S0_TXD0
**             ----------------------------------------------------
**
**         Port name                   : PTC
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : 0x0002
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : GPIOC_PDOR [0x400FF080]
**         Port control register       : GPIOC_PDDR [0x400FF094]
**
**         Optimization for            : speed
**     Contents    :
**         SetDir - void S0_Rodilla_SetDir(bool Dir);
**         GetVal - bool S0_Rodilla_GetVal(void);
**         PutVal - void S0_Rodilla_PutVal(bool Val);
**         ClrVal - void S0_Rodilla_ClrVal(void);
**         SetVal - void S0_Rodilla_SetVal(void);
**         NegVal - void S0_Rodilla_NegVal(void);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file S0_Rodilla.h
** @version 01.00
** @brief
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
*/         
/*!
**  @addtogroup S0_Rodilla_module S0_Rodilla module documentation
**  @{
*/         

#ifndef __S0_Rodilla_H
#define __S0_Rodilla_H

/* MODULE S0_Rodilla. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "BitIoLdd1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 




/*
** ===================================================================
**     Method      :  S0_Rodilla_SetDir (component BitIO)
**     Description :
**         This method sets direction of the component.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Dir        - Direction to set (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
**     Returns     : Nothing
** ===================================================================
*/
#define S0_Rodilla_SetDir(Dir) (BitIoLdd1_SetDir(BitIoLdd1_DeviceData, (Dir)))

/*
** ===================================================================
**     Method      :  S0_Rodilla_GetVal (component BitIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define S0_Rodilla_GetVal() (BitIoLdd1_GetVal(BitIoLdd1_DeviceData))

/*
** ===================================================================
**     Method      :  S0_Rodilla_PutVal (component BitIO)
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
#define S0_Rodilla_PutVal(Val) (BitIoLdd1_PutVal(BitIoLdd1_DeviceData, (Val)))

/*
** ===================================================================
**     Method      :  S0_Rodilla_ClrVal (component BitIO)
**     Description :
**         This method clears (sets to zero) the output value.
**           a) direction = Input  : sets the output value to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define S0_Rodilla_ClrVal() (BitIoLdd1_ClrVal(BitIoLdd1_DeviceData))

/*
** ===================================================================
**     Method      :  S0_Rodilla_SetVal (component BitIO)
**     Description :
**         This method sets (sets to one) the output value.
**           a) direction = Input  : sets the output value to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define S0_Rodilla_SetVal() (BitIoLdd1_SetVal(BitIoLdd1_DeviceData))

/*
** ===================================================================
**     Method      :  S0_Rodilla_NegVal (component BitIO)
**     Description :
**         This method negates (inverts) the output value.
**           a) direction = Input  : inverts the output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly inverts the value
**                                   of the appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define S0_Rodilla_NegVal() (BitIoLdd1_NegVal(BitIoLdd1_DeviceData))

/* END S0_Rodilla. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __S0_Rodilla_H */
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
