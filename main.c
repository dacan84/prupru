#include <msp430.h> 
#include <driverlib/MSP430FR57xx/driverlib.h>
#include <driverlib/MSP430FR57xx/inc/hw_memmap.h>
#include "src/grace/_Grace.h"
#include "ligth_sensor_MAX44009.h"
/*
 * main.c
 */

uint8_t ligthHigh = 0;
uint8_t ligthLow = 0;
int main(void) {

	Grace_init();

	while (1) {
		EUSCI_B_I2C_enable(EUSCI_B0_BASE);

		EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
		EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, SLV_ADDR1);

		EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, LUX_LOW_ADDR);
		while (EUSCI_B_I2C_SENDING_STOP
				== EUSCI_B_I2C_masterIsStopSent(EUSCI_B0_BASE))
			;
		EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_MODE);
		EUSCI_B_I2C_masterSendStart(EUSCI_B0_BASE);
		ligthLow = EUSCI_B_I2C_masterReceiveSingle(EUSCI_B0_BASE);
		while (EUSCI_B_I2C_SENDING_STOP
				== EUSCI_B_I2C_masterIsStopSent(EUSCI_B0_BASE))
			;




		//FIXME desde aqui funciona con el enable de la primera linea del while

		EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE); //EUSCI_B_I2C_RECEIVE_MODE
		EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, SLV_ADDR1);
		//	while(EUSCI_B_I2C_BUS_BUSY==EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

		EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, LUX_HIGH_ADDR);
		while (EUSCI_B_I2C_SENDING_STOP
				== EUSCI_B_I2C_masterIsStopSent(EUSCI_B0_BASE))
			;
		EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_MODE); //EUSCI_B_I2C_RECEIVE_MODE

		EUSCI_B_I2C_masterSendStart(EUSCI_B0_BASE);
		ligthHigh = EUSCI_B_I2C_masterReceiveSingle(EUSCI_B0_BASE);
		//FIXME: HASTA AQUI FUNCIONA.
		while (EUSCI_B_I2C_SENDING_STOP
				== EUSCI_B_I2C_masterIsStopSent(EUSCI_B0_BASE))
			;


//		EUSCI_B_I2C_disable(EUSCI_B0_BASE);
	}
}
