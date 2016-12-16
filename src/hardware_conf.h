/*
 * hardware_conf.h
 *
 *  Created on: 22. 11. 2016
 *      Author: Luk�
 */

#ifndef HARDWARE_CONF_H_
#define HARDWARE_CONF_H_

//LED
#define LED_Pin GPIO_Pin_5
#define LED_GPIO GPIOA

//USART
#define USART USART2
#define USART_TX_Pin GPIO_Pin_2
#define USART_RX_Pin GPIO_Pin_3
#define USART_TX_PinSource GPIO_PinSource2
#define USART_RX_PinSource GPIO_PinSource3
#define USART_GPIO GPIOA

//ADC
#define ADC_Periph ADC1
#define ADC_CH0_Pin GPIO_Pin_0
#define ADC_CH0_GPIO GPIOA
#define ADC_Channel_SetT ADC_Channel_0

#define ADC_CH1_Pin GPIO_Pin_1
#define ADC_CH1_GPIO GPIOA
#define ADC_Channel_RealT ADC_Channel_1

//TIM Tvz
#define TIM_Tvz_Periph TIM3

//Deklar�cia funkci�
void Init_RCC();
void Init_GPIO();
void Init_USART();
void Init_ADC();
void Init_Timer_Tvz();
void Heat_State(FunctionalState state);
void Delay(uint32_t cycles);
void Send_Buffer(char *Buffer); //Spustenie poselania cez preru�enie
uint16_t ADC_Meranie_SetT(); //Odmeria a vr�ti hodnontu ADC
uint16_t ADC_Meranie_RealT();


#endif /* HARDWARE_CONF_H_ */
