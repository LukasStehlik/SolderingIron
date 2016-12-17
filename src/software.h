/*
 * software.h
 *
 *  Created on: 29. 11. 2016
 *      Author: Lukáš
 */

#ifndef SOFTWARE_H_
#define SOFTWARE_H_

#define Hyst 1

#define PlotX0 6
#define PlotY0 122
#define PlotSizeX 117
#define PlotSizeY 80

typedef struct
{
	uint16_t SetTemperature;
	uint16_t RealTemperature;
	char *TX_Buffer;
	uint16_t RealTempBuffer[PlotSizeX-1];
	uint16_t RealTempBuffer_Last[PlotSizeX-1];
	uint16_t SetTempBuffer[PlotSizeX-1];
	uint16_t SetTempBuffer_Last[PlotSizeX-1];
	FunctionalState Buffer_Lock;
	uint8_t Buffer_Counter;
}Values_Struct;

#define OP_AMP_Gain (1+100/2.2)

void Timer_Tvz_Callback();
void Print_Intro(uint32_t duration);
void Print_MainScreen();
void Init_Buffer();
void Add_To_Buffer(uint16_t* buffer,uint16_t value);
void Print_Plot(uint16_t* buffer,uint16_t color);
void Clear_Plot(uint16_t* buffer);
void Copy_Buffer(uint16_t* From,uint16_t* To);

#endif /* SOFTWARE_H_ */
