/*
 * harware_conf.h
 *
 *  Created on: 22. 11. 2016
 *      Author: Lukáš
 */

#ifndef HARWARE_CONF_H_
#define HARWARE_CONF_H_

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

//Deklarácia funkcií
void Init_RCC();
void Init_GPIO();
void Init_USART();
void Init_ADC();
void Delay(uint32_t cycles);
void Send_Buffer(char* Buffer); //Spustenie poselania cez prerušenie



#endif /* HARWARE_CONF_H_ */
