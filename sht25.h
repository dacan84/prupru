/*
 * SHT25.h
 *
 *  Created on: 8/7/2015
 *      Author: Diego
 */

#ifndef SHT25_H_
#define SHT25_H_

#include <stdint.h>

#define SHT25_SLV_ADDR          0b1000000
#define SHT25_T_MEAS_HM			0b11100011
#define SHT25_RH_MEAS_HM		0b11100101
#define SHT25_T_MEAS_NOT_HM		0b11110011
#define SHT25_RH_MEAS_NOT_HM	0b11110101
#define SHT25_TRIGGER_T_MEAS	0b11110011
#define SHT25_TRIGGER_RH_MEAS	0b11110101

#define	SHT25_CONFIG_REG_WRITE_ADDR 	0b1100110
#define	SHT25_CONFIG_REG_READ_ADDR 		0b1100111
/*No hace falta tocar el SHT25Config en principio.*/
#define SHT25_SOFT_RESET		0b11111110

typedef struct {
		uint16_t	temperature;
		uint16_t	relativeHumidity;
} Sht25Data;

typedef struct {
		float	temperature;
		float	relativeHumidity;
} Sht25RealData;

Sht25RealData AddSht25Measure(void);

#endif /* SHT25_H_ */
