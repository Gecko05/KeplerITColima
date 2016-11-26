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
#include "CS1.h"
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
#define Baja 12000
#define Media 2
#define Alta 3

int bandera = 0;

char orden_articulacion;
char orden_modo;					
int orden_angulo;

volatile int bandera_actualizar;

byte datoi2c[6];
int16 gx,gy,ax,ay,az,gz;
int16 hx,hy,vx,vy,vz,hz;
byte memAddr = 0x3B;
byte memAddr1 = 0x43;
int repeticiones;
float Acc[4];
float Gy[4];
float Angle[4];
int angulo[4];
volatile char orden[5];
#define A_R 16384.0
#define G_R 131.0
#define pwmgm  0x6B;
#define RAD_TO_DEG  57.295779

int i,j;

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
	int repeticiones;
}Articulacion;
int electro;
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
			
			if(Rodilla.angulo_nuevo>Rodilla.angulo_actual){
				S0_Rodilla_SetVal();
				S1_Rodilla_ClrVal();
				PWM_Rodilla_SetDutyUS(20000);
			}
			else if(Rodilla.angulo_nuevo<Rodilla.angulo_actual){
				S0_Rodilla_ClrVal();
				S1_Rodilla_SetVal();
				PWM_Rodilla_SetDutyUS(10000);
			}
			else if(Rodilla.angulo_nuevo==Rodilla.angulo_actual){
				S0_Rodilla_ClrVal();
				S1_Rodilla_ClrVal();
				orden[1] = 'N';
				orden_articulacion = 'N';
			}
			break;
		case 'C':										//	C A D E R A		F L E X I O N
			//CaderaF.angulo_nuevo = (angulo*(float)(2/3))-60;
			CaderaF.angulo_nuevo = angulo;
			if(CaderaF.angulo_nuevo<CaderaF.angulo_actual){
				PWM_Cadera_Flexion_SetDutyUS(1000);
				S0_Cadera_Flexion_SetVal();
				S1_Cadera_Flexion_ClrVal();
			}
			else if(CaderaF.angulo_nuevo>CaderaF.angulo_actual){
				PWM_Cadera_Flexion_SetDutyUS(15000);
				S0_Cadera_Flexion_ClrVal();
				S1_Cadera_Flexion_SetVal();
			}
			else if(CaderaF.angulo_nuevo==CaderaF.angulo_actual){
				S0_Cadera_Flexion_ClrVal();
				S1_Cadera_Flexion_ClrVal();
				orden[1] = 'N';
				orden_articulacion = 'N';
			}
			break;
		case 'A':										//	C A D E R A		A D U C C I O N
			CaderaA.angulo_nuevo = angulo;
			PWM_Cadera_Aduccion_SetDutyUS(20000);
			if(CaderaA.angulo_nuevo>CaderaA.angulo_actual){
				S0_Cadera_Aduccion_SetVal();
				S1_Cadera_Aduccion_ClrVal();
			}
			else if(CaderaA.angulo_nuevo<CaderaA.angulo_actual){
				S0_Cadera_Aduccion_ClrVal();
				S1_Cadera_Aduccion_SetVal();
			}
			else{
				S0_Cadera_Aduccion_ClrVal();
				S1_Cadera_Aduccion_ClrVal();
				orden_articulacion = 'N';
			}
			break;
		case 'T':										//	T O B I L L O
			Tobillo.angulo_nuevo = (float)angulo/((float)(0.07))+18000;
			Tobillo.angulo_actual = Tobillo.angulo_nuevo;
			PWM_Tobillo_SetDutyUS(Tobillo.angulo_actual);
			
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
		
		//Rodilla.angulo_actual = angulo[0];
		
		//CaderaF.angulo_actual = angulo[0];
		//Rodilla.angulo_actual = angulo[2];
		if(bandera_actualizar == 1){
		GI2C1_ReadAddress(0x68,&memAddr,1,&datoi2c[0],6);
		//GI2C1_ReadByteAddress8(0x68,memAddr,&datoi2c[0]);
		ax = ((datoi2c[0]<<8) | (datoi2c[1]));
		ay = ((datoi2c[2]<<8) | (datoi2c[3]));
		az = ((datoi2c[4]<<8) | (datoi2c[5]));
		Acc[1] = atan(-1*(az/A_R)/sqrt(powf((ay/A_R),2) + powf((ax/A_R),2)))*RAD_TO_DEG;
		Acc[0] = atan((ay/A_R)/sqrt(powf((az/A_R),2) + powf((ax/A_R),2)))*RAD_TO_DEG;
		GI2C1_ReadAddress(0x68,&memAddr1,1,&datoi2c[0],6);
		gx = ((datoi2c[0]<<8) | (datoi2c[1]));
		gy = ((datoi2c[2]<<8) | (datoi2c[3]));
		gz = ((datoi2c[4]<<8) | (datoi2c[5]));
		Gy[0] = gz/G_R;
		Gy[1] = gy/G_R;
		Angle[0] = 0.98 *(Angle[0]-Gy[0]*0.02) + 0.02*Acc[0];
		Angle[1] = 0.98 *(Angle[1]-Gy[1]*0.02) + 0.02*Acc[1];
		angulo[0] = Angle[0];
		angulo[1] = Angle[1];	

		
		GI2C1_ReadAddress(0x69,&memAddr,1,&datoi2c[0],6);
		//GI2C1_ReadByteAddress8(0x68,memAddr,&datoi2c[0]);
		vx = ((datoi2c[0]<<8) | (datoi2c[1]));
		vy = ((datoi2c[2]<<8) | (datoi2c[3]));
		vz = ((datoi2c[4]<<8) | (datoi2c[5]));
		Acc[3] = atan(-1*(vz/A_R)/sqrt(powf((vy/A_R),2) + powf((vx/A_R),2)))*RAD_TO_DEG;
		Acc[2] = atan((vy/A_R)/sqrt(powf((vz/A_R),2) + powf((vx/A_R),2)))*RAD_TO_DEG;
		GI2C1_ReadAddress(0x69,&memAddr1,1,&datoi2c[0],6);
		hx = ((datoi2c[0]<<8) | (datoi2c[1]));
		hy = ((datoi2c[2]<<8) | (datoi2c[3]));
		hz = ((datoi2c[4]<<8) | (datoi2c[5]));
		Gy[2] = hz/G_R;
		Gy[3] = hy/G_R;
		Angle[2] = 0.98 *(Angle[2]-Gy[2]*0.010) + 0.02*Acc[2];
		Angle[3] = 0.98 *(Angle[3]-Gy[3]*0.010) + 0.02*Acc[3];
		angulo[2] = Angle[2];
		angulo[3] = Angle[3];
		Rodilla.angulo_actual = Acc[2]+30;
		CaderaF.angulo_actual = Acc[0];
		bandera_actualizar = 0;
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
	
	
void tipo_orden(void){
	orden_modo = orden[0];
	orden_articulacion = orden[1];
	orden_angulo = ((orden[2]-'0')*100) + ((orden[3]-'0')*10)+((orden[4]-'0'));
	if(orden_articulacion=='E'){
			MODO = RUTINA;
			orden_modo = 'R';
	}
	else if(orden_articulacion=='F'){
		electro = 0;
	}
	switch(orden_modo){
	case 'A':
		MODO = AJUSTE;
		break;
	case 'R':
		MODO = RUTINA;
		break;
	case 'B':
		S0_Cadera_Flexion_ClrVal();
		S1_Cadera_Flexion_ClrVal();
		break;
	}
}
	

/*void repeticiones(char articulacion,int repeticiones){
	switch(articulacion){
	case 'C':
		CaderaF.repeticiones = repeticiones;
		break;
	case 'R':
		Rodilla.repeticiones = repeticiones;
		break;
	case 'T':
		Tobillo.repeticiones = repeticiones;
		break;
	}
}*/
	
	
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{

	Rodilla.angulo_actual = 50;
	CaderaF.angulo_actual = 50;
	CaderaA.angulo_actual = 50;
	Tobillo.angulo_actual = 40;
	//Rodilla.angulo_nuevo = 0;
	
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /**########################################################################################################################
   * 									R U T I N A     P R I N C I P A L
   * ########################################################################################################################
   */
  DA1_Init(NULL);
  GI2C1_Init();
 // S1_Cadera_Flexion_SetVal();
  //S0_Cadera_Flexion_ClrVal();
  //S1_Cadera_Aduccion_SetVal();
  //S0_Cadera_Aduccion_ClrVal();

  //PWM_Cadera_Aduccion_SetDutyUS(19999);
  PWM_Cadera_Flexion_SetDutyUS(20000);
  //PWM_Cadera_Flexion_Disable();PWM_Cadera_Aduccion_Disable();PWM_Rodilla_Disable();
  PWM_Tobillo_SetDutyUS(18000);
  GI2C1_WriteByteAddress8(0x68,0x6B,0);
  GI2C1_WriteByteAddress8(0x69,0x6B,0);
  PWM_Tobillo_SetDutyUS(18000);
  for(;;){
	  //actualizar_angulos();
	  tipo_orden();
	  while(MODO==AJUSTE){
		  tipo_orden();
		  actualizar_angulos();
		  
		  if(orden_modo=='X'){
			  captura_maximo(orden_articulacion);
		  }
		  else if(orden_modo=='Y'){
			  captura_minimo(orden_articulacion);
		  }
		  /*else if(orden_modo=='U'){
			  repeticiones(orden_articulacion,orden_angulo);
		  }*/
		  else if(orden_modo=='W'){
		  	 repeticiones = orden_angulo;
		  }
		  ajustar_angulo(orden_articulacion,orden_angulo);
		  
/*#######################################################
 * 
 */

	  }
	  while(MODO==RUTINA){
		  for(i=0;i<repeticiones;i++){
			  while(CaderaF.angulo_actual!=CaderaF.angulo_minimo){
				  actualizar_angulos();
				  ajustar_angulo('C',CaderaF.angulo_minimo);
			  }
			  while(CaderaF.angulo_actual!=CaderaF.angulo_maximo){
				  actualizar_angulos();
				  ajustar_angulo('C',CaderaF.angulo_maximo);
			  }
		  }
		  for(i=0;i<=repeticiones;i++){
			  while(Rodilla.angulo_actual!=Rodilla.angulo_minimo){
				  actualizar_angulos();
				  ajustar_angulo('R',Rodilla.angulo_minimo);
			  }
			  while(Rodilla.angulo_actual!=CaderaF.angulo_maximo){
				  actualizar_angulos();
				  ajustar_angulo('R',CaderaF.angulo_maximo);
			  }
		  }
		  for(i=0;i<=repeticiones;i++){
			  while(Tobillo.angulo_actual!=CaderaF.angulo_minimo){
				  actualizar_angulos();
				  ajustar_angulo('T',Tobillo.angulo_minimo);
			  }
			  while(Tobillo.angulo_actual!=CaderaF.angulo_maximo){
				  actualizar_angulos();
				  ajustar_angulo('T',Tobillo.angulo_maximo);
			  }
		  }
		  MODO=AJUSTE;
		  orden_modo = 'A';
		  orden_articulacion = 'h';
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
