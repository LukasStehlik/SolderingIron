/*
 * hardware_conf.c
 *
 *  Created on: 22. 11. 2016
 *      Author: Lukáš
 */

#include <stddef.h>
#include "stm32l1xx.h"
#include "harware_conf.h"

char* TX_Buffer;


//Implementácia funkcií
void Init_RCC()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

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

	ADC_StructInit(&adc);
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

void Send_Buffer(char* Buffer)
{
	TX_Buffer=Buffer;
	USART_ITConfig(USART,USART_IT_TXE,ENABLE);
}
