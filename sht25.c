/*
 * sht25.c
 *
 *  Created on: 8/7/2015
 *      Author: Diego
 */

#include "sht25.h"
#include <driverlib/MSP430FR57xx/driverlib.h>
#include <math.h>

static float CalculateTemperature(uint16_t T);
static float CalculateRelativeHumidity(uint16_t RH);
static Sht25Data AddSht25Values (void);
static void TriggerMeasureTHoldMasterSHT25 (void);
static void TriggerMeasureRHHoldMasterSHT25 (void);
static uint16_t AddSht25Temperature (void);
static uint16_t AddSht25RelativeHumidity (void);
static void delay (unsigned int i);

Sht25RealData AddSht25Measure(void){
	Sht25Data sht25Data;
	Sht25RealData sht25RealData;

	sht25Data = AddSht25Values();
	sht25RealData.temperature = CalculateTemperature(sht25Data.temperature);
	sht25RealData.relativeHumidity = CalculateRelativeHumidity(sht25Data.relativeHumidity);
	return sht25RealData;
}

static float CalculateTemperature(uint16_t T){
	float temperature;

	temperature = -46.85+175.72*(T/65536);

	return temperature;
}

static float CalculateRelativeHumidity (uint16_t RH){
	float relativeHumidity;

	relativeHumidity = -6+125*(RH/65536);

	return relativeHumidity;
}

static Sht25Data AddSht25Values (void){
	Sht25Data sht25Data;

	EUSCI_B_I2C_enable(EUSCI_B0_BASE);
	EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE,SHT25_SLV_ADDR);

	TriggerMeasureTHoldMasterSHT25();
	delay(2);
	sht25Data.temperature = AddSht25Temperature();

	TriggerMeasureRHHoldMasterSHT25();
	delay(2);
	sht25Data.relativeHumidity = AddSht25RelativeHumidity();

	EUSCI_B_I2C_disable(EUSCI_B0_BASE);

	return sht25Data;
}

static uint16_t AddSht25Temperature (void){
	uint8_t msb;
	uint8_t lsb;
	uint8_t check;
	uint16_t temperature;

	EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE,SHT25_T_MEAS_NOT_HM);
	while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
	EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

	msb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//msb = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);
	//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
	lsb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//lsb = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);

	check = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//EUSCI_B_I2C_masterReceiveMultiByteFinish(EUSCI_B0_BASE);
	EUSCI_B_I2C_masterReceiveMultiByteStop(EUSCI_B0_BASE);
	//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

	temperature = ((msb<<8)+lsb);

	return temperature;
}

static uint16_t AddSht25RelativeHumidity (void){
	uint8_t msb;
	uint8_t lsb;
	uint8_t check;
	uint16_t relativeHumidity;

	EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE,SHT25_RH_MEAS_NOT_HM);
	while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
	EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

	msb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//msb = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);
	//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
	lsb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//lsb = EUSCI_B_I2C_masterReceiveSingleByte(EUSCI_B0_BASE);

	check = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
	//EUSCI_B_I2C_masterReceiveMultiByteFinish(EUSCI_B0_BASE);
	EUSCI_B_I2C_masterReceiveMultiByteStop(EUSCI_B0_BASE);
	//while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

	return relativeHumidity;
}

static void TriggerMeasureTHoldMasterSHT25 (void){
		EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, SHT25_TRIGGER_T_MEAS);
		while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

}
static void TriggerMeasureRHHoldMasterSHT25 (void){
		EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE, SHT25_TRIGGER_RH_MEAS);
		while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
}

static void delay (unsigned int i){
	unsigned int j = 0;
	for (j=0; j<i; ++j){
		for (j=0; j<256; ++j){}
	}
}
