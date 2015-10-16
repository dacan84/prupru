/*
 * System.h
 *
 *  Created on: 10/9/2015
 *      Author: Diego
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


//---------- Includes ----------------------------------------------------------
#include "msp430.h"             // controller register definitions
#include <assert.h>                // assert functions
#include <intrinsics.h>            // low level microcontroller commands
#include "typedefs.h"              // type definitions

//---------- Enumerations ------------------------------------------------------
// Error codes
typedef enum{
  ACK_ERROR                = 0x01,
  TIME_OUT_ERROR           = 0x02,
  CHECKSUM_ERROR           = 0x04,
  UNIT_ERROR               = 0x08
}etError;



//==============================================================================
void DelayMicroSeconds (uint32_t nbrOfUs);
//==============================================================================
// wait function for small delays
// input:  nbrOfUs   wait x times approx. one micro second (fcpu = 4MHz)
// return: -
// note: smallest delay is approx. 30us due to function call


#endif /* SYSTEM_H_ */
