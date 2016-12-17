/*
 * software.c
 *
 *  Created on: 29. 11. 2016
 *      Author: Lukáš
 */

#include <stddef.h>
#include <stdio.h>
#include "stm32l1xx.h"
#include "software.h"
#include "hardware_conf.h"
#include "ili9163.h"

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

	if(values.Buffer_Counter>=9)
	{
		values.Buffer_Counter=0;
		if(values.Buffer_Lock==DISABLE)
		{
			Add_To_Buffer(values.RealTempBuffer,values.RealTemperature);
			Add_To_Buffer(values.SetTempBuffer,values.SetTemperature);
		}
	}
	else values.Buffer_Counter++;
}

void Print_Intro(uint32_t duration)
{
	lcdInitialise(LCD_ORIENTATION2);
	lcdClearDisplay(decodeRgbValue(255, 255, 255));
	lcdPutS("Polacek Palenik", 20, 17, decodeRgbValue(25,69,98), decodeRgbValue(255,255,255));
	lcdPutS("Stehlik Trecer", 24, 37, decodeRgbValue(25,69,98), decodeRgbValue(255,255,255));
	lcdPutS("Soldering ", 35, 57, decodeRgbValue(0,125,98), decodeRgbValue(255,255,255));
	lcdPutS("iron", 55, 77, decodeRgbValue(0,125,98), decodeRgbValue(255,255,255));
	Delay(duration);
}

void Print_MainScreen()
{
	char buffer[30];
	sprintf(buffer,"SetTemp:%d°C  ",values.SetTemperature);
	lcdPutS(buffer, 10, 5, decodeRgbValue(0,0,255), decodeRgbValue(255,255,255));
	sprintf(buffer,"RealTemp:%d°C  ",values.RealTemperature);
	lcdPutS(buffer, 10, 20, decodeRgbValue(255,0,0), decodeRgbValue(255,255,255));

	lcdPutS("T(t)", 57, PlotY0-PlotSizeY-9, decodeRgbValue(0,0,0), decodeRgbValue(255,255,255));

	lcdLine(PlotX0,PlotY0,PlotX0+PlotSizeX,PlotY0,decodeRgbValue(0,0,0));
	lcdLine(PlotX0+PlotSizeX,PlotY0,PlotX0+PlotSizeX-5,PlotY0-5,decodeRgbValue(0,0,0));
	lcdLine(PlotX0+PlotSizeX,PlotY0,PlotX0+PlotSizeX-5,PlotY0+5,decodeRgbValue(0,0,0));

	lcdLine(PlotX0,PlotY0,PlotX0,PlotY0-PlotSizeY,decodeRgbValue(0,0,0));
	lcdLine(PlotX0,PlotY0-PlotSizeY,PlotX0+5,PlotY0-PlotSizeY+5,decodeRgbValue(0,0,0));
	lcdLine(PlotX0,PlotY0-PlotSizeY,PlotX0-5,PlotY0-PlotSizeY+5,decodeRgbValue(0,0,0));

	values.Buffer_Lock=ENABLE;

	Clear_Plot(values.RealTempBuffer_Last);
	Clear_Plot(values.SetTempBuffer_Last);

	Print_Plot(values.RealTempBuffer,decodeRgbValue(255,0,0));
	Print_Plot(values.SetTempBuffer,decodeRgbValue(0,0,255));

	Copy_Buffer(values.RealTempBuffer,values.RealTempBuffer_Last);
	Copy_Buffer(values.SetTempBuffer,values.SetTempBuffer_Last);

	values.Buffer_Lock=DISABLE;
}

void Init_Buffer(uint16_t* buffer)
{
	uint8_t i;
	for(i=0;i<PlotSizeX-1;i++)
	{
		buffer[i]=0;
	}
}

void Add_To_Buffer(uint16_t* buffer,uint16_t value)
{
	uint8_t i;
	for(i=0;i<PlotSizeX-2;i++)
	{
		buffer[i]=buffer[i+1];
	}
	buffer[PlotSizeX-2]=value;
}

void Copy_Buffer(uint16_t* From,uint16_t* To)
{
	uint8_t i;
	for(i=0;i<PlotSizeX-1;i++)
	{
		To[i]=From[i];
	}
}

void Print_Plot(uint16_t* buffer,uint16_t color)
{
	int i;
	uint8_t x0,x1;
	uint8_t y0,y1;

	for(i=0;i<PlotSizeX-2;i++)
	{
		x0=i+1;
		x1=i+2;
		y0=buffer[i]*PlotSizeY/320;
		y1=buffer[i+1]*PlotSizeY/320;
		lcdLine(PlotX0+x0,PlotY0-y0-1,PlotX0+x1,PlotY0-y1-1,color);
	}
}

void Clear_Plot(uint16_t* buffer)
{
	int i;
	uint8_t x0,x1;
	uint8_t y0,y1;

	for(i=0;i<PlotSizeX-2;i++)
	{
		x0=i+1;
		x1=i+2;
		y0=buffer[i]*PlotSizeY/320;
		y1=buffer[i+1]*PlotSizeY/320;
		lcdLine(PlotX0+x0,PlotY0-y0-1,PlotX0+x1,PlotY0-y1-1,decodeRgbValue(255,255,255));
	}
}
