/*
 * software.c
 *
 *  Created on: 29. 11. 2016
 *      Author: Lukáš
 */

#include <stddef.h>
#include "stm32l1xx.h"
#include "software.h"
#include "hardware_conf.h"



void Timer_Tvz_Callback()
{
	uint16_t AD_value;
	AD_value=ADC_Meranie();
}
