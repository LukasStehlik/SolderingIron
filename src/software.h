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
	uint16_t SetTemperature; //Premenná pre výpoèet nastavenej teploty
	uint16_t RealTemperature; //Premenná pre výpoèet skutoènej teploty
	char *TX_Buffer; //Buffer pre USART
	uint16_t RealTempBuffer[PlotSizeX-1]; //Buffer pre graf
	uint16_t RealTempBuffer_Last[PlotSizeX-1]; //Buffer pre staré hodnoty grafu kvôli jeho mazaniu
	uint16_t SetTempBuffer[PlotSizeX-1];
	uint16_t SetTempBuffer_Last[PlotSizeX-1];
	FunctionalState Buffer_Lock; //Zamknutie zápisu do bufferu pri jeho vykres¾ovaní
	uint8_t Buffer_Counter; //Opozdenie pridávania do bufferu každej 10 vzorky
}Values_Struct;

#define OP_AMP_Gain (1+100/2.2)

void Timer_Tvz_Callback();
void Print_Intro(uint32_t duration);
void Print_MainScreen();
void Init_Buffer(); //iniciálizácia bufferu na hodnotu 0
void Add_To_Buffer(uint16_t* buffer,uint16_t value);
void Print_Plot(uint16_t* buffer,uint16_t color);
void Clear_Plot(uint16_t* buffer);
void Copy_Buffer(uint16_t* From,uint16_t* To);

#endif /* SOFTWARE_H_ */
