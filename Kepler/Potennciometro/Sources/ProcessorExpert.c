/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL46Z256VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-27, 20:33, # CodeGen: 0
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
#include "AD1.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
#include "PTC.h"
#include "Bit1.h"
#include "BitIoLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

uint16_t adc[2000];

int i;
int suma;
int promedio;
int angulo;
extern uint16_t grados[51];
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  for(i=0;i<2000;i++){
		  AD1_Measure(1);
		  AD1_GetValue16(&adc[i]);
	  }
	  for(i=0;i<2000;i++){
		  suma+=adc[i];
	  }
	  promedio=suma/2000;
	  suma = 0;
	  /*if((promedio>=19643)&&(promedio<20606)){
	  angulo = 0+((float)5/963)*((float)promedio-19643);}
	  else if((promedio>=20606)&&(promedio<21689)){
	  angulo = 5+((float)5/1083)*((float)promedio-20606);}
	  else if((promedio>=21689)&&(promedio<22850)){
	  angulo = 10+((float)5/1161)*((float)promedio-21689);}
	  else if((promedio>=22850)&&(promedio<23775)){
	  angulo = 15+((float)5/925)*((float)promedio-22850);}
	  else if((promedio>=23775)&&(promedio<24894)){
	  angulo = 20+((float)5/1119)*((float)promedio-23775);}
	  else if((promedio>=24894)&&(promedio<25946)){
	  angulo = 25+((float)5/1052)*((float)promedio-24894);}
	  else if((promedio>=25946)&&(promedio<27172)){
	  angulo = 30+((float)5/1226)*((float)promedio-25946);}
	  else if((promedio>=27172)&&(promedio<28215)){
	  angulo = 35+((float)5/1043)*((float)promedio-27172);}
	  else if((promedio>=28215)&&(promedio<29027)){
	  angulo = 40+((float)5/812)*((float)promedio-28215);}
	  else if((promedio>=29027)&&(promedio<29973)){
	  angulo = 45+((float)5/946)*((float)promedio-29027);}
	  else if((promedio>=29973)&&(promedio<31018)){
	  angulo = 50+((float)5/1045)*((float)promedio-29973);}
	  else if((promedio>=31018)&&(promedio<32133)){
	  angulo = 55+((float)5/1115)*((float)promedio-31018);}
	  else if((promedio>=32133)&&(promedio<33030)){
	  angulo = 60+((float)5/897)*((float)promedio-32133);}
	  else if((promedio>=33030)&&(promedio<34323)){
	  angulo = 65+((float)5/1293)*((float)promedio-33030);}
	  else if((promedio>=34323)&&(promedio<35584)){
	  angulo = 70+((float)5/1261)*((float)promedio-34323);}
	  else if((promedio>=35584)&&(promedio<36697)){
	  angulo = 75+((float)5/1113)*((float)promedio-35584);}
	  else if((promedio>=36697)&&(promedio<37847)){
	  angulo = 80+((float)5/1150)*((float)promedio-36697);}
	  else if((promedio>=37847)&&(promedio<38836)){
	  angulo = 85+((float)5/989)*((float)promedio-37847);}
	  else if((promedio>=38836)&&(promedio<39969)){
	  angulo = 90+((float)5/1133)*((float)promedio-38836);}
	  else if((promedio>=39969)&&(promedio<41269)){
	  angulo = 95+((float)5/1300)*((float)promedio-39969);}
	  else if((promedio>=41269)&&(promedio<42433)){
	  angulo = 100+((float)5/1164)*((float)promedio-41269);}
	  else if((promedio>=42433)&&(promedio<43763)){
	  angulo = 105+((float)5/1330)*((float)promedio-42433);}
	  else if((promedio>=43763)&&(promedio<44915)){
	  angulo = 110+((float)5/1152)*((float)promedio-43763);}
	  else if((promedio>=44915)&&(promedio<46348)){
	  angulo = 115+((float)5/1433)*((float)promedio-44915);}
	  else if((promedio>=46348)&&(promedio<47475)){
	  angulo = 120+((float)5/1127)*((float)promedio-46348);}
	  else if((promedio>=47475)&&(promedio<48935)){
	  angulo = 125+((float)5/1460)*((float)promedio-47475);}
	  else if((promedio>=48935)&&(promedio<50153)){
	  angulo = 130+((float)5/1218)*((float)promedio-48935);}
	  else if((promedio>=50153)&&(promedio<51683)){
	  angulo = 135+((float)5/1530)*((float)promedio-50153);}
	  else if((promedio>=51683)&&(promedio<52795)){
	  angulo = 140+((float)5/1112)*((float)promedio-51683);}
	  else if((promedio>=52795)&&(promedio<54149)){
	  angulo = 145+((float)5/1354)*((float)promedio-52795);}
	  else if((promedio>=54149)&&(promedio<55022)){
	  angulo = 150+((float)5/873)*((float)promedio-54149);}
	  else if((promedio>=55022)&&(promedio<56651)){
	  angulo = 155+((float)5/1629)*((float)promedio-55022);}
	  else if((promedio>=56651)&&(promedio<57527)){
	  angulo = 160+((float)5/876)*((float)promedio-56651);}
	  else if((promedio>=57527)&&(promedio<59001)){
	  angulo = 165+((float)5/1474)*((float)promedio-57527);}
	  else if((promedio>=59001)&&(promedio<60020)){
	  angulo = 170+((float)5/1019)*((float)promedio-59001);}
	  else if((promedio>=60020)&&(promedio<61036)){
	  angulo = 175+((float)5/1016)*((float)promedio-60020);}
	  	  
	  else if((promedio>=61133)&&(promedio<62286)){
	  angulo = 180+((float)5/1153)*((float)promedio-61133);}
	  
	  else if((promedio>=62286)&&(promedio<63464)){
	  angulo = 185+((float)5/1178)*((float)promedio-62286);}
	  
	  else if((promedio>=63464)&&(promedio<64326)){
	  angulo = 190+((float)5/862)*((float)promedio-63464);}
	  
	  else if((promedio>=64326)&&(promedio<65320)){
	  angulo = 195+((float)5/994)*((float)promedio-64326);}
	  */
	 /*
	  if((promedio>=19755)&&(promedio<20924)){
	  angulo = 0+((float)5/1169)*((float)promedio-19755);}
	  else if((promedio>=20924)&&(promedio<21756)){
	  angulo = 5+((float)5/832)*((float)promedio-20924);}
	  else if((promedio>=21756)&&(promedio<22850)){
	  angulo = 10+((float)5/1094)*((float)promedio-21756);}
	  else if((promedio>=22850)&&(promedio<23904)){
	  angulo = 15+((float)5/1054)*((float)promedio-22850);}
	  else if((promedio>=23904)&&(promedio<25075)){
	  angulo = 20+((float)5/1171)*((float)promedio-23904);}
	  else if((promedio>=25075)&&(promedio<25907)){
	  angulo = 25+((float)5/832)*((float)promedio-25075);}
	  else if((promedio>=25907)&&(promedio<27107)){
	  angulo = 30+((float)5/1200)*((float)promedio-25907);}
	  else if((promedio>=27107)&&(promedio<28133)){
	  angulo = 35+((float)5/1026)*((float)promedio-27107);}
	  else if((promedio>=28133)&&(promedio<29306)){
	  angulo = 40+((float)5/1173)*((float)promedio-28133);}
	  else if((promedio>=29306)&&(promedio<30201)){
	  angulo = 45+((float)5/895)*((float)promedio-29306);}
	  else if((promedio>=30201)&&(promedio<31344)){
	  angulo = 50+((float)5/1143)*((float)promedio-30201);}
	  else if((promedio>=31344)&&(promedio<32331)){
	  angulo = 55+((float)5/987)*((float)promedio-31344);}
	  else if((promedio>=32331)&&(promedio<33550)){
	  angulo = 60+((float)5/1219)*((float)promedio-32331);}
	  else if((promedio>=33550)&&(promedio<34567)){
	  angulo = 65+((float)5/1017)*((float)promedio-33550);}
	  else if((promedio>=34567)&&(promedio<35741)){
	  angulo = 70+((float)5/1174)*((float)promedio-34567);}
	  else if((promedio>=35741)&&(promedio<36923)){
	  angulo = 75+((float)5/1182)*((float)promedio-35741);}
	  else if((promedio>=36923)&&(promedio<37992)){
	  angulo = 80+((float)5/1069)*((float)promedio-36923);}
	  else if((promedio>=37992)&&(promedio<39125)){
	  angulo = 85+((float)5/1133)*((float)promedio-37992);}
	  else if((promedio>=39125)&&(promedio<40360)){
	  angulo = 90+((float)5/1235)*((float)promedio-39125);}
	  else if((promedio>=40360)&&(promedio<41544)){
	  angulo = 95+((float)5/1184)*((float)promedio-40360);}
	  else if((promedio>=41544)&&(promedio<42922)){
	  angulo = 100+((float)5/1378)*((float)promedio-41544);}
	  else if((promedio>=42922)&&(promedio<44105)){
	  angulo = 105+((float)5/1183)*((float)promedio-42922);}
	  else if((promedio>=44105)&&(promedio<45548)){
	  angulo = 110+((float)5/1443)*((float)promedio-44105);}
	  else if((promedio>=45548)&&(promedio<46732)){
	  angulo = 115+((float)5/1184)*((float)promedio-45548);}
	  else if((promedio>=46732)&&(promedio<48074)){
	  angulo = 120+((float)5/1342)*((float)promedio-46732);}
	  else if((promedio>=48074)&&(promedio<49256)){
	  angulo = 125+((float)5/1182)*((float)promedio-48074);}
	  else if((promedio>=49256)&&(promedio<50673)){
	  angulo = 130+((float)5/1417)*((float)promedio-49256);}
	  else if((promedio>=50673)&&(promedio<51985)){
	  angulo = 135+((float)5/1312)*((float)promedio-50673);}
	  else if((promedio>=51985)&&(promedio<53050)){
	  angulo = 140+((float)5/1065)*((float)promedio-51985);}
	  else if((promedio>=53050)&&(promedio<54350)){
	  angulo = 145+((float)5/1300)*((float)promedio-53050);}
	  else if((promedio>=54350)&&(promedio<55569)){
	  angulo = 150+((float)5/1219)*((float)promedio-54350);}
	  else if((promedio>=55569)&&(promedio<56597)){
	  angulo = 155+((float)5/1028)*((float)promedio-55569);}
	  else if((promedio>=56597)&&(promedio<57807)){
	  angulo = 160+((float)5/1210)*((float)promedio-56597);}
	  else if((promedio>=57807)&&(promedio<58969)){
	  angulo = 165+((float)5/1162)*((float)promedio-57807);}
	  else if((promedio>=58969)&&(promedio<60062)){
	  angulo = 170+((float)5/1093)*((float)promedio-58969);}
	  else if((promedio>=60062)&&(promedio<61015)){
	  angulo = 175+((float)5/953)*((float)promedio-60062);}
	  else if((promedio>=61015)&&(promedio<62196)){
	  angulo = 180+((float)5/1181)*((float)promedio-61015);}
	  else if((promedio>=62196)&&(promedio<63084)){
	  angulo = 185+((float)5/888)*((float)promedio-62196);}
	  else if((promedio>=63084)&&(promedio<64302)){
	  angulo = 190+((float)5/1218)*((float)promedio-63084);}
	  else if((promedio>=64302)&&(promedio<65191)){
	  angulo = 195+((float)5/889)*((float)promedio-64302);}
	  else if((promedio>=65191)&&(promedio<65534)){
	  angulo = 200+((float)5/343)*((float)promedio-65191);}
	  */
	  
	  if((promedio>=grados[1])&&(promedio<grados[2])){
	  angulo =5+((float)5/grados[2]-grados[1])*((float)promedio-grados[1]);}
	  else if((promedio>=grados[2])&&(promedio<grados[3])){
	  angulo =10+((float)5/grados[3]-grados[2])*((float)promedio-grados[2]);}
	  else if((promedio>=grados[3])&&(promedio<grados[4])){
	  angulo =15+((float)5/grados[4]-grados[3])*((float)promedio-grados[3]);}
	  else if((promedio>=grados[4])&&(promedio<grados[5])){
	  angulo =20+((float)5/grados[5]-grados[4])*((float)promedio-grados[4]);}
	  else if((promedio>=grados[5])&&(promedio<grados[6])){
	  angulo =25+((float)5/grados[6]-grados[5])*((float)promedio-grados[5]);}
	  else if((promedio>=grados[6])&&(promedio<grados[7])){
	  angulo =30+((float)5/grados[7]-grados[6])*((float)promedio-grados[6]);}
	  else if((promedio>=grados[7])&&(promedio<grados[8])){
	  angulo =35+((float)5/grados[8]-grados[7])*((float)promedio-grados[7]);}
	  else if((promedio>=grados[8])&&(promedio<grados[9])){
	  angulo =40+((float)5/grados[9]-grados[8])*((float)promedio-grados[8]);}
	  else if((promedio>=grados[9])&&(promedio<grados[10])){
	  angulo =45+((float)5/grados[10]-grados[9])*((float)promedio-grados[9]);}
	  else if((promedio>=grados[10])&&(promedio<grados[11])){
	  angulo =50+((float)5/grados[11]-grados[10])*((float)promedio-grados[10]);}
	  else if((promedio>=grados[11])&&(promedio<grados[12])){
	  angulo =55+((float)5/grados[12]-grados[11])*((float)promedio-grados[11]);}
	  else if((promedio>=grados[12])&&(promedio<grados[13])){
	  angulo =60+((float)5/grados[13]-grados[12])*((float)promedio-grados[12]);}
	  else if((promedio>=grados[13])&&(promedio<grados[14])){
	  angulo =65+((float)5/grados[14]-grados[13])*((float)promedio-grados[13]);}
	  else if((promedio>=grados[14])&&(promedio<grados[15])){
	  angulo =70+((float)5/grados[15]-grados[14])*((float)promedio-grados[14]);}
	  else if((promedio>=grados[15])&&(promedio<grados[16])){
	  angulo =75+((float)5/grados[16]-grados[15])*((float)promedio-grados[15]);}
	  else if((promedio>=grados[16])&&(promedio<grados[17])){
	  angulo =80+((float)5/grados[17]-grados[16])*((float)promedio-grados[16]);}
	  else if((promedio>=grados[17])&&(promedio<grados[18])){
	  angulo =85+((float)5/grados[18]-grados[17])*((float)promedio-grados[17]);}
	  else if((promedio>=grados[18])&&(promedio<grados[19])){
	  angulo =90+((float)5/grados[19]-grados[18])*((float)promedio-grados[18]);}
	  else if((promedio>=grados[19])&&(promedio<grados[20])){
	  angulo =95+((float)5/grados[20]-grados[19])*((float)promedio-grados[19]);}
	  else if((promedio>=grados[20])&&(promedio<grados[21])){
	  angulo =100+((float)5/grados[21]-grados[20])*((float)promedio-grados[20]);}
	  else if((promedio>=grados[21])&&(promedio<grados[22])){
	  angulo =105+((float)5/grados[22]-grados[21])*((float)promedio-grados[21]);}
	  else if((promedio>=grados[22])&&(promedio<grados[23])){
	  angulo =110+((float)5/grados[23]-grados[22])*((float)promedio-grados[22]);}
	  else if((promedio>=grados[23])&&(promedio<grados[24])){
	  angulo =115+((float)5/grados[24]-grados[23])*((float)promedio-grados[23]);}
	  else if((promedio>=grados[24])&&(promedio<grados[25])){
	  angulo =120+((float)5/grados[25]-grados[24])*((float)promedio-grados[24]);}
	  else if((promedio>=grados[25])&&(promedio<grados[26])){
	  angulo =125+((float)5/grados[26]-grados[25])*((float)promedio-grados[25]);}
	  else if((promedio>=grados[26])&&(promedio<grados[27])){
	  angulo =130+((float)5/grados[27]-grados[26])*((float)promedio-grados[26]);}
	  else if((promedio>=grados[27])&&(promedio<grados[28])){
	  angulo =135+((float)5/grados[28]-grados[27])*((float)promedio-grados[27]);}
	  else if((promedio>=grados[28])&&(promedio<grados[29])){
	  angulo =140+((float)5/grados[29]-grados[28])*((float)promedio-grados[28]);}
	  else if((promedio>=grados[29])&&(promedio<grados[30])){
	  angulo =145+((float)5/grados[30]-grados[29])*((float)promedio-grados[29]);}
	  else if((promedio>=grados[30])&&(promedio<grados[31])){
	  angulo =150+((float)5/grados[31]-grados[30])*((float)promedio-grados[30]);}
	  else if((promedio>=grados[31])&&(promedio<grados[32])){
	  angulo =155+((float)5/grados[32]-grados[31])*((float)promedio-grados[31]);}
	  else if((promedio>=grados[32])&&(promedio<grados[33])){
	  angulo =160+((float)5/grados[33]-grados[32])*((float)promedio-grados[32]);}
	  else if((promedio>=grados[33])&&(promedio<grados[34])){
	  angulo =165+((float)5/grados[34]-grados[33])*((float)promedio-grados[33]);}
	  else if((promedio>=grados[34])&&(promedio<grados[35])){
	  angulo =170+((float)5/grados[35]-grados[34])*((float)promedio-grados[34]);}
	  else if((promedio>=grados[35])&&(promedio<grados[36])){
	  angulo =175+((float)5/grados[36]-grados[35])*((float)promedio-grados[35]);}
	  else if((promedio>=grados[36])&&(promedio<grados[37])){
	  angulo =180+((float)5/grados[37]-grados[36])*((float)promedio-grados[36]);}
	  else if((promedio>=grados[37])&&(promedio<grados[38])){
	  angulo =185+((float)5/grados[38]-grados[37])*((float)promedio-grados[37]);}
	  else if((promedio>=grados[38])&&(promedio<grados[39])){
	  angulo =190+((float)5/grados[39]-grados[38])*((float)promedio-grados[38]);}
	  else if((promedio>=grados[39])&&(promedio<grados[40])){
	  angulo =195+((float)5/grados[40]-grados[39])*((float)promedio-grados[39]);}
	  else if((promedio>=grados[40])&&(promedio<grados[41])){
	  angulo =200+((float)5/grados[41]-grados[40])*((float)promedio-grados[40]);}
	  else if((promedio>=grados[41])&&(promedio<grados[42])){
	  angulo =205+((float)5/grados[42]-grados[41])*((float)promedio-grados[41]);}
	  else if((promedio>=grados[42])&&(promedio<grados[43])){
	  angulo =210+((float)5/grados[43]-grados[42])*((float)promedio-grados[42]);}
	  else if((promedio>=grados[43])&&(promedio<grados[44])){
	  angulo =215+((float)5/grados[44]-grados[43])*((float)promedio-grados[43]);}
	  else if((promedio>=grados[44])&&(promedio<grados[45])){
	  angulo =220+((float)5/grados[45]-grados[44])*((float)promedio-grados[44]);}
	  else if((promedio>=grados[45])&&(promedio<grados[46])){
	  angulo =225+((float)5/grados[46]-grados[45])*((float)promedio-grados[45]);}
	  else if((promedio>=grados[46])&&(promedio<grados[47])){
	  angulo =230+((float)5/grados[47]-grados[46])*((float)promedio-grados[46]);}
	  else if((promedio>=grados[47])&&(promedio<grados[48])){
	  angulo =235+((float)5/grados[48]-grados[47])*((float)promedio-grados[47]);}
	  else if((promedio>=grados[48])&&(promedio<grados[49])){
	  angulo =240+((float)5/grados[49]-grados[48])*((float)promedio-grados[48]);}
	  else if((promedio>=grados[49])&&(promedio<grados[50])){
	  angulo =245+((float)5/grados[50]-grados[49])*((float)promedio-grados[49]);}
	  else if((promedio>=grados[50])&&(promedio<grados[51])){
	  angulo =250+((float)5/grados[51]-grados[50])*((float)promedio-grados[50]);}
	  
	  if(angulo>=0){
	  Term1_SendChar('p');
	  Term1_SendNum(angulo);
	  Term1_SendChar('\r');
	  Term1_SendChar('\n');
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
