/*
 * software.h
 *
 *  Created on: 29. 11. 2016
 *      Author: Luk�
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
	uint16_t SetTemperature; //Premenn� pre v�po�et nastavenej teploty
	uint16_t RealTemperature; //Premenn� pre v�po�et skuto�nej teploty
	char *TX_Buffer; //Buffer pre USART
	uint16_t RealTempBuffer[PlotSizeX-1]; //Buffer pre graf
	uint16_t RealTempBuffer_Last[PlotSizeX-1]; //Buffer pre star� hodnoty grafu kv�li jeho mazaniu
	uint16_t SetTempBuffer[PlotSizeX-1];
	uint16_t SetTempBuffer_Last[PlotSizeX-1];
	FunctionalState Buffer_Lock; //Zamknutie z�pisu do bufferu pri jeho vykres�ovan�
	uint8_t Buffer_Counter; //Opozdenie prid�vania do bufferu ka�dej 10 vzorky
}Values_Struct;

#define OP_AMP_Gain (1+100/2.2)

void Timer_Tvz_Callback();
void Print_Intro(uint32_t duration);
void Print_MainScreen();
void Init_Buffer(); //inici�liz�cia bufferu na hodnotu 0
void Add_To_Buffer(uint16_t* buffer,uint16_t value);
void Print_Plot(uint16_t* buffer,uint16_t color);
void Clear_Plot(uint16_t* buffer);
void Copy_Buffer(uint16_t* From,uint16_t* To);

#endif /* SOFTWARE_H_ */
