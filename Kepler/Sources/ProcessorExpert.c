/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL46Z256VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-26, 15:38, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
#include "S0_Cadera_Aduccion.h"
#include "BitIoLdd3.h"
#include "S1_Cadera_Aduccion.h"
#include "BitIoLdd4.h"
#include "S0_Cadera_Flexion.h"
#include "BitIoLdd5.h"
#include "S1_Cadera_Flexion.h"
#include "BitIoLdd6.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "DA1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Math.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#define Baja 1
#define Media 2
#define Alta 3

volatile char orden_articulacion;
volatile char orden_modo;					
volatile int orden_angulo;

byte datoi2c[6];
int gx,gy,ax,ay,az;
byte memAddr = 0x3B;
byte memAddr1 = 0x43;
float Acc[2];
float Angle[2];
float Gy[2];
#define A_R 16384.0
#define G_R 131.0
#define pwmgm  0x6B;
#define RAD_TO_DEG  57.295779
int angulo[2];
char envio[3];


enum MODOS{
	AJUSTE,
	RUTINA
};
volatile enum MODOS MODO;

typedef struct Articulacion{
	int angulo_actual;
	int angulo_minimo;
	int angulo_maximo;
	int angulo_nuevo;
}Articulacion;

Articulacion Rodilla;
Articulacion CaderaF;
Articulacion CaderaA;
Articulacion Tobillo;

/*
** ===================================================================
**     Funcion       :  ajustar_angulo
**
**     Descripcion :
**         Compara y ajusta los angulos de cada articulacion
**         segun se especifique en la orden.
**         
**     Parametros  : articulacion, angulo
**     Regresa     : Nada
** ===================================================================
*/
	void ajustar_angulo(char articulacion,int angulo){
		switch(articulacion){
		case 'R':										//	R O D I L L A
			Rodilla.angulo_nuevo = angulo;
			PWM_Rodilla_SetDutyUS(Baja);
			if(Rodilla.angulo_nuevo>Rodilla.angulo_actual){
				S0_Rodilla_SetVal();
				S1_Rodilla_ClrVal();
			}
			else if(Rodilla.angulo_nuevo<Rodilla.angulo_actual){
				S0_Rodilla_ClrVal();
				S1_Rodilla_SetVal();
			}
			else{
				S0_Rodilla_ClrVal();
				S1_Rodilla_ClrVal();
			}
			break;
		case 'C':										//	C A D E R A		F L E X I O N
			CaderaF.angulo_nuevo = angulo;
			PWM_Cadera_Flexion_SetDutyUS(Baja);
			if(CaderaF.angulo_nuevo>CaderaF.angulo_actual){
				S0_Cadera_Aduccion_SetVal();
				S1_Cadera_Aduccion_ClrVal();
			}
			else if(CaderaF.angulo_nuevo<CaderaF.angulo_actual){
				S0_Cadera_Aduccion_ClrVal();
				S1_Cadera_Aduccion_SetVal();
			}
			else{
				S0_Cadera_Aduccion_ClrVal();
				S1_Cadera_Aduccion_ClrVal();
			}
			break;
		case 'A':										//	C A D E R A		A D U C C I O N
			CaderaA.angulo_nuevo = angulo;
			PWM_Cadera_Aduccion_SetDutyUS(Baja);
			if(CaderaA.angulo_nuevo>CaderaA.angulo_actual){
				S0_Cadera_Flexion_SetVal();
				S1_Cadera_Flexion_ClrVal();
			}
			else if(CaderaA.angulo_nuevo<CaderaA.angulo_actual){
				S0_Cadera_Flexion_ClrVal();
				S1_Cadera_Flexion_SetVal();
			}
			else{
				S0_Cadera_Flexion_ClrVal();
				S1_Cadera_Flexion_ClrVal();
			}
			break;
		case 'T':										//	T O B I L L O
			Tobillo.angulo_nuevo = angulo;
			break;
		default:
			break;
		}
	}
	
/*
** ===================================================================
**     Funcion       :  actualizar_angulos
**
**     Descripcion :
**         Llama las funciones de i2c para medir los angulos 
**         y asigna el correspondiente a cada articulacion
**         
**     Parametros  : Nada
**     Regresa     : Nada
** ===================================================================
*/
	void actualizar_angulos(void){
		//i2c();
		//Rodilla.angulo_actual = angulo[0];
		CaderaF.angulo_actual = angulo[0];
	}

/*
** ===================================================================
**     Funcion       :  captura_maximo
**
**     Descripcion :
**         Guarda el angulo capturado como angulo maximo
**         
**     Parametros  : articulacion
**     Regresa     : Nada
** ===================================================================
*/	
	void captura_maximo(char articulacion){
		switch(articulacion){
		case 'R':
			Rodilla.angulo_maximo = Rodilla.angulo_actual;
			break;
		case 'C':
			CaderaF.angulo_maximo = CaderaF.angulo_actual;
			break;
		case 'A':
			CaderaA.angulo_maximo = CaderaA.angulo_actual;
			break;
		case 'T':
			Tobillo.angulo_maximo = Tobillo.angulo_actual;
			break;
		default:
			break;
		}
	}
	
/*
** ===================================================================
**     Funcion       :  captura_maximo
**
**     Descripcion :
**         Guarda el angulo capturado como angulo maximo
**         
**     Parametros  : articulacion
**     Regresa     : Nada
** ===================================================================
*/	
	void captura_minimo(char articulacion){
		switch(articulacion){
		case 'R':
			Rodilla.angulo_minimo = Rodilla.angulo_actual;
			break;
		case 'C':
			CaderaF.angulo_minimo = CaderaF.angulo_actual;
			break;
		case 'A':
			CaderaA.angulo_minimo = CaderaA.angulo_actual;
			break;
		case 'T':
			Tobillo.angulo_minimo = Tobillo.angulo_actual;
			break;
		default:
			break;
		}
	}
	
	
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{

	Rodilla.angulo_actual = 50;
	CaderaF.angulo_actual = 50;
	CaderaA.angulo_actual = 50;
	//Rodilla.angulo_nuevo = 0;
	
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /**########################################################################################################################
   * 									R U T I N A     P R I N C I P A L
   * ########################################################################################################################
   */
  DA1_Init(NULL);
  PWM_Tobillo_Disable();
  GI2C1_Init();
  GI2C1_WriteByteAddress8(0x68,0x6B,0);
  PWM_Tobillo_Enable();
  //S1_Cadera_Flexion_SetVal();
  //S0_Cadera_Flexion_ClrVal();
  S1_Cadera_Aduccion_SetVal();
  S0_Cadera_Aduccion_ClrVal();
  PWM_Cadera_Aduccion_SetDutyUS(19999);
  PWM_Cadera_Flexion_SetDutyUS(19999);
  PWM_Rodilla_SetDutyUS(19999);
  for(;;){
	  while(MODO==AJUSTE){
		  actualizar_angulos();
		  if(orden_modo=='X'){
			  captura_maximo(orden_articulacion);
		  }
		  else if(orden_modo=='Y'){
			  captura_minimo(orden_articulacion);
		  }
		  ajustar_angulo(orden_articulacion,orden_angulo);
/*#######################################################
 * 
 */
			GI2C1_ReadAddress(0x68,&memAddr,1,&datoi2c[0],6);
			//GI2C1_ReadByteAddress8(0x68,memAddr,&datoi2c[0]);
			ax = ((datoi2c[0]<<8) | (datoi2c[1]));
			ay = ((datoi2c[2]<<8) | (datoi2c[3]));
			az = ((datoi2c[4]<<8) | (datoi2c[5]));
			Acc[1] = atan(-1*(ax/A_R)/sqrt(powf((ay/A_R),2) + powf((az/A_R),2)))*RAD_TO_DEG;
			Acc[0] = atan((ay/A_R)/sqrt(powf((ax/A_R),2) + powf((az/A_R),2)))*RAD_TO_DEG;
			GI2C1_ReadAddress(0x68,&memAddr1,1,&datoi2c[0],4);
			gx = ((datoi2c[0]<<8) | (datoi2c[1]));
			gy = ((datoi2c[2]<<8) | (datoi2c[3]));
			Gy[0] = gx/G_R;
			Gy[1] = gy/G_R;
			Angle[0] = 0.98 *(Angle[0]+Gy[0]*0.010) + 0.02*Acc[0];
			Angle[1] = 0.98 *(Angle[1]+Gy[1]*0.010) + 0.02*Acc[1];
			angulo[0] = Angle[0];
			angulo[1] = Angle[1];
			/*#######################################################
			 * 
			 */
			/*envio[0] = ((angulo[0])/100)%10;
			envio[1] = ((angulo[0])/10)%10;
			envio[2] = ((angulo[0])/1)%10;
			AS1_SendChar(envio[2]);
			AS1_SendChar(envio[1]);
			AS1_SendChar(envio[0]);
			AS1_SendChar('c');
			AS1_SendChar('\n');*/
	  }
	  while(MODO==RUTINA){
		  
	  }
	  
  }

  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
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
