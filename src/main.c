
/* Includes */
#include <stddef.h>
#include <stdio.h>
#include "stm32l1xx.h"
#include "hardware_conf.h"
#include "software.h"
#include "spi.h"
#include "ili9163.h"
#include "string.h"
extern void (*TIM_Tvz_IRQ_Callback)(void);
extern Values_Struct values;

int main(void)
{
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	RCC_PLLCmd(DISABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==SET);
	RCC_PLLConfig(RCC_PLLSource_HSI,RCC_PLLMul_4,RCC_PLLDiv_2);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);


	TIM_Tvz_IRQ_Callback=Timer_Tvz_Callback;//Priradenie funkcie pre meranie napätie na Channel0

	Init_RCC();
	Init_GPIO();
	Init_USART();
	Init_ADC();
	Init_Timer_Tvz();

	initSPI();
	initCD_Pin();
	initCS_Pin();
	initRES_Pin();

	Print_Intro(8000000);
	Init_Buffer(values.RealTempBuffer_Last);
	Init_Buffer(values.RealTempBuffer);
	Init_Buffer(values.SetTempBuffer_Last);
	Init_Buffer(values.SetTempBuffer);

	values.Buffer_Lock=DISABLE;
	values.Buffer_Counter=0;

	lcdClearDisplay(decodeRgbValue(255, 255, 255));
	while (1)
	{
		/*sprintf(buffer,"RT->%d°C\n\rST->%d°C\n\r",values.RealTemperature,values.SetTemperature);
		Send_Buffer(buffer);*/

		if((values.Buffer_Counter)%5==0) Print_MainScreen();
		Delay(10000);

	}
	return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
