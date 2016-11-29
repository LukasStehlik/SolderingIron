/*
 * hardware_conf.c
 *
 *  Created on: 22. 11. 2016
 *      Author: Lukáš
 */

#include <stddef.h>
#include "stm32l1xx.h"
#include "hardware_conf.h"

char *TX_Buffer;
void (*TIM_Tvz_IRQ_Callback)(void);


//Implementácia funkcií
void Init_RCC()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

}

void Init_GPIO()
{
	GPIO_InitTypeDef gpio;

	//Nastavenie GPIO pre LED2
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode=GPIO_Mode_OUT;
	gpio.GPIO_Pin=LED_Pin;
	GPIO_Init(LED_GPIO,&gpio);

	//Nastavenie GPIO pre USART2
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode=GPIO_Mode_AF;
	gpio.GPIO_Pin=USART_RX_Pin | USART_TX_Pin;
	gpio.GPIO_Speed=GPIO_Speed_40MHz;
	GPIO_Init(USART_GPIO,&gpio);
	GPIO_PinAFConfig(USART_GPIO,USART_TX_PinSource,GPIO_AF_USART2);
	GPIO_PinAFConfig(USART_GPIO,USART_RX_PinSource,GPIO_AF_USART2);

	//Nastavenie GPIO pre ADC1
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode=GPIO_Mode_AN;
	gpio.GPIO_Pin=ADC_CH0_Pin;
	GPIO_Init(ADC_CH0_GPIO,&gpio);


}

void Init_USART()
{
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;

	USART_StructInit(&usart);
	usart.USART_BaudRate=9600*2;
	usart.USART_Mode=USART_Mode_Tx;
	USART_Init(USART,&usart);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	nvic.NVIC_IRQChannel=USART2_IRQn;
	nvic.NVIC_IRQChannelCmd=ENABLE;
	nvic.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic);

	USART_Cmd(USART,ENABLE);
}

void Init_ADC()
{
	ADC_InitTypeDef adc;

	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);

	ADC_StructInit(&adc);
	ADC_Init(ADC_Periph,&adc);
	ADC_RegularChannelConfig(ADC_Periph,ADC_Channel,1,ADC_SampleTime_384Cycles);

	ADC_Cmd(ADC_Periph,ENABLE);
	while(ADC_GetFlagStatus(ADC_Periph,ADC_FLAG_ADONS)==RESET);
}

void Init_Timer_Tvz()
{
	TIM_TimeBaseInitTypeDef timTB;
	NVIC_InitTypeDef nvic;

	TIM_TimeBaseStructInit(&timTB);
	timTB.TIM_Period=1000;
	timTB.TIM_Prescaler=16000;
	TIM_TimeBaseInit(TIM_Tvz_Periph,&timTB);
	TIM_ITConfig(TIM_Tvz_Periph,TIM_IT_Update,ENABLE);

	nvic.NVIC_IRQChannel=TIM3_IRQn;
	nvic.NVIC_IRQChannelCmd=ENABLE;
	nvic.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic);

	TIM_Cmd(TIM_Tvz_Periph,ENABLE);
}

void TIM3_IRQHandler()
{
	if(TIM_GetFlagStatus(TIM_Tvz_Periph,TIM_FLAG_Update))
	{
		TIM_Tvz_IRQ_Callback();
		TIM_ClearFlag(TIM_Tvz_Periph,TIM_FLAG_Update);
	}
}

void Delay(uint32_t cycles)
{
	while(cycles--);
}

void TX_Interrupt_ChangeState(FunctionalState NewState)
{
	USART_ITConfig(USART,USART_IT_TXE,NewState);
}

void USART2_IRQHandler()
{
	char c;
	if(USART_GetFlagStatus(USART,USART_FLAG_TXE))
	{
		c=*TX_Buffer++;
		if(c) USART_SendData(USART,c);
		else USART_ITConfig(USART,USART_IT_TXE,DISABLE);
	}
}

void Send_Buffer(char *Buffer)
{
	TX_Buffer=Buffer;
	USART_ITConfig(USART,USART_IT_TXE,ENABLE);
}

uint16_t ADC_Meranie()
{
	ADC_SoftwareStartConv(ADC_Periph);
	while(ADC_GetFlagStatus(ADC_Periph,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC_Periph);
}
