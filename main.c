#include <msp430.h> 
#include <driverlib/MSP430FR57xx/driverlib.h>
#include <driverlib/MSP430FR57xx/inc/hw_memmap.h>
#include "src/grace/_Grace.h"
#include "ligth_sensor_MAX44009.h"
#include "typedefs.h"
#include "SHT2x.h"          //header file for SHT2x functions
#include "I2C_HAL.h"        //header file for I2C hardware abstraction
#include "System.h"         //header file for system settings
#include <stdio.h>          //header file standard input / output functions



/*
 * main.c
 */

//uint8_t ligthHigh = 0;
//uint8_t ligthLow = 0;
uint16_t humidity = 0;
uint16_t temperature = 0;
//Sht25RealData measures;

int main(void) {
	 // variables
	  uint8_t  error = 0;              //variable for error code. For codes see system.h
	 // uint8_t  userRegister;           //variable for user register
	 // bt   endOfBattery;           //variable for end of battery

	  nt16 sRH;                    //variable for raw humidity ticks
	  float   humidityRH;             //variable for relative humidity[%RH] as float
	  nt16 sT;                     //variable for raw temperature ticks
	  float   temperatureC;           //variable for temperature[°C] as float
	  //uint8_t  SerialNumber_SHT2x[8];  //64bit serial number

	  Grace_init();
	  //Init_HW();                   //initializes Hardware (osc, watchdog,...)
	  I2c_Init();                  //initializes uC-ports for I2C
	  DelayMicroSeconds(15000);    //wait for sensor initialization t_powerUp (15ms)

	  //note: The following code segments show how to use the different functions
	  //      of SHT2x. The loop does not show a typical sequence in an application

	//Grace_init();

	while (1) {


		error = 0;                                       // reset error status
		   /* // --- Reset sensor by command ---
		    error |= SHT2x_SoftReset();

		    // --- Read the sensors serial number (64bit) ---
		    error |= SHT2x_GetSerialNumber(SerialNumber_SHT2x);

		    // --- Set Resolution e.g. RH 10bit, Temp 13bit ---
		    error |= SHT2x_ReadUserRegister(&userRegister);  //get actual user reg
		    userRegister = (userRegister & ~SHT2x_RES_MASK) | SHT2x_RES_10_13BIT;
		    error |= SHT2x_WriteUserRegister(&userRegister); //write changed user reg
		*/
		    // --- measure humidity with "Polling Mode" (no hold master) ---
		    error |= SHT2x_MeasurePoll(HUMIDITY, &sRH);
		    // --- measure temperature with "Polling Mode" (no hold master) ---
		    error |= SHT2x_MeasurePoll(TEMP, &sT);

		    //-- calculate humidity and temperature --
		    temperatureC = SHT2x_CalcTemperatureC(sT.u16);
		    humidityRH   = SHT2x_CalcRH(sRH.u16);

		 /*   // --- check end of battery status (eob)---
		    // note: a RH / Temp. measurement must be executed to update the status of eob
		    error |= SHT2x_ReadUserRegister(&userRegister);  //get actual user reg
		    if( (userRegister & SHT2x_EOB_MASK) == SHT2x_EOB_ON ) endOfBattery = true;
		    else endOfBattery = false;
		*/

		//measures = AddSht25Measure();

		//EUSCI_B_I2C_enable(EUSCI_B0_BASE);

		//EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, LUX_HIGH_ADDR);
		//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

		//ligthHigh = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);
		//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));


		//EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, LUX_LOW_ADDR);
		//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

		//ligthLow = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);
		//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

		//EUSCI_B_I2C_disable(EUSCI_B0_BASE);

	}
}
