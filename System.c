/*
 * System.c
 *
 *  Created on: 10/9/2015
 *      Author: Diego
 */


//---------- Includes ----------------------------------------------------------
#include "System.h"

//==============================================================================
//#pragma optimize = s none
void DelayMicroSeconds (uint32_t nbrOfUs)
//==============================================================================
{
	uint32_t i=0;
  for(i=0; i<nbrOfUs; i++)
  {
	  __delay_cycles(1);//TODO: ajustyar para que sea un segundo.
	  //__asm("nop");  //nop's may be added for timing adjustment
  }
}
