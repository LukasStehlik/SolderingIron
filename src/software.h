/*
 * software.h
 *
 *  Created on: 29. 11. 2016
 *      Author: Lukáš
 */

#ifndef SOFTWARE_H_
#define SOFTWARE_H_

#define Hyst 1

typedef struct
{
	uint16_t SetTemperature;
	uint16_t RealTemperature;
	char *TX_Buffer;
}Values_Struct;

#define OP_AMP_Gain (1+100/2.2)

void Timer_Tvz_Callback();

#endif /* SOFTWARE_H_ */
