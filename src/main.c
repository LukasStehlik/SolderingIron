
/* Includes */
#include <stddef.h>
#include <stdio.h>
#include "stm32l1xx.h"
#include "harware_conf.h"

extern char* TX_Buffer;


int main(void)
{
	char buffer[10];
	Init_RCC();
	Init_GPIO();
	Init_USART();
	//Init_ADC();

	GPIO_SetBits(LED_GPIO,LED_Pin);
	Delay(1000000);
	GPIO_ResetBits(LED_GPIO,LED_Pin);
	Delay(1000000);

	sprintf(buffer,"Hello\n\r");
	while (1)
	{
		Send_Buffer(buffer);
		Delay(5000000);
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
