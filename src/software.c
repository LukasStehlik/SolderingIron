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

Values_Struct values;

void Timer_Tvz_Callback()
{
	double temp;
	uint16_t AD_value;

	AD_value=ADC_Meranie_SetT();
	values.SetTemperature=(AD_value*260.0/4095)+40;

	AD_value=ADC_Meranie_RealT();
	temp=AD_value*3300.0/4095.0;
	temp=temp/OP_AMP_Gain;
	values.RealTemperature=(uint16_t)(7.51*temp+30.5);

	if(values.RealTemperature<(values.SetTemperature-Hyst)) Heat_State(ENABLE);
	if(values.RealTemperature>(values.SetTemperature+Hyst)) Heat_State(DISABLE);
}
