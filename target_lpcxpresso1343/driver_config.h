/*
 * driver_config.h
 *
 *  Created on: Aug 31, 2010
 *      Author: nxp28548
 */

#ifndef DRIVER_CONFIG_H_
#define DRIVER_CONFIG_H

#include <LPC13xx.h>

#define CONFIG_ENABLE_DRIVER_CRP						1
#define CONFIG_CRP_SETTING_NO_CRP						1

#define CONFIG_ENABLE_DRIVER_ADC						1
#define CONFIG_ADC_ENABLE_ADC_IRQHANDLER 0 	/* 1 is interrupt driven, 0 is polling */

#define CONFIG_ENABLE_DRIVER_PRINTF						1

 /* DRIVER_CONFIG_H_ */
#endif