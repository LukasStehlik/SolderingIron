
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

	TIM_Tvz_IRQ_Callback=Timer_Tvz_Callback;//Priradenie funkcie pre meranie napätie na Channel0

	char buffer[30];
	Init_RCC();
	Init_GPIO();
	Init_USART();
	Init_ADC();

	initSPI2();
	initCD_Pin();
	initCS_Pin();
	initRES_Pin();

	Init_Timer_Tvz();

	GPIO_SetBits(LED_GPIO,LED_Pin);
	Delay(1000000);
	GPIO_ResetBits(LED_GPIO,LED_Pin);
	Delay(1000000);

	lcdInitialise(LCD_ORIENTATION2);
	lcdClearDisplay(decodeRgbValue(255, 255, 255));
	lcdPutS("Polacek Palenik", 20, 17, decodeRgbValue(25,69,98), 0xFFFF);
	lcdPutS("Stehlik Trecer", 24, 37, decodeRgbValue(25,69,98), 0xFFFF);
	lcdPutS("Soldering ", 35, 57, decodeRgbValue(0,125,98), 0xFFFF);
	lcdPutS("iron", 55, 77, decodeRgbValue(0,125,98), 0xFFFF);

	Delay(1000000);
	Delay(1000000);

	lcdClearDisplay(decodeRgbValue(255, 255, 255));
	uint8_t counter=0;
	char  temp[10];
	while (1)
	{
	//	sprintf(buffer,"RT->%d°C\n\rST->%d°C\n\r",values.RealTemperature,values.SetTemperature);
	//	Send_Buffer(buffer);
		counter++;
		Delay(20000);
		sprintf(temp,"Set:%d  ",counter);
		lcdPutS(temp, 10, 5, decodeRgbValue(25,69,255), 0xFFFF);
		sprintf(temp,"Read:%d  ",counter);
		lcdPutS(temp, 10, 20, decodeRgbValue(0,0,255), 0xFFFF);
		if(counter==128)counter=0;
		lcdCircle(90,15,5,decodeRgbValue(255,0,0));

		lcdPlot(counter,128-counter,decodeRgbValue(0,0,255));
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
