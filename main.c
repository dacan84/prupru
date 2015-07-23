#include <msp430.h> 
#include <driverlib/MSP430FR57xx/driverlib.h>
#include <driverlib/MSP430FR57xx/inc/hw_memmap.h>
#include "src/grace/_Grace.h"
#include "ligth_sensor_MAX44009.h"
#include "sht25.h"

/*
 * main.c
 */

//uint8_t ligthHigh = 0;
//uint8_t ligthLow = 0;
uint16_t humidity = 0;
uint16_t temperature = 0;
Sht25RealData measures;

int main(void) {

	Grace_init();

	while (1) {

		measures = AddSht25Measure();

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
