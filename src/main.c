/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32F10x Standard Peripherals Library
**
**  Distribution: The file is distributed "as is", without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32f10x.h"

#ifdef USE_STM3210B_EVAL
 #include "stm3210b_eval.h"
 #include "stm3210b_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval.h"
 #include "stm3210e_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval.h"
 #include "stm3210c_eval_lcd.h"
 #include "stm3210c_eval_i2c_ee.h"
 #define USE_BOARD
 #define USE_LED
 #define USE_SEE
#elif defined USE_STM32100B_EVAL
 #include "stm32100b_eval.h"
 #include "stm32100b_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval.h"
 #include "stm32100e_eval_lcd.h"
 #include "stm32100e_eval_i2c_ee.h"
 #define USE_BOARD
 #define USE_LED
 #define USE_SEE
#elif defined USE_STM32_DISCOVERY
 #include "STM32vldiscovery.h"
#elif defined USE_IAR_STM32F103ZE
 #include "board.h"
 #define USE_LED
#elif defined USE_KEIL_MCBSTM32
 #include "board.h"
 #define USE_LED
#endif


/* Private typedef */
/* Private define  */
#ifdef USE_STM3210B_EVAL
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210B-EVAL    "
  #define MESSAGE4   "                    "
#elif defined USE_STM3210E_EVAL
  #define MESSAGE1   " STM32 High Density "
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210E-EVAL    "
  #define MESSAGE4   "                    "
#elif defined USE_STM3210C_EVAL
  #define MESSAGE1   " STM32 Connectivity "
  #define MESSAGE2   " Line Device running"
  #define MESSAGE3   " on STM3210C-EVAL   "
  #define MESSAGE4   "                    "
#elif defined USE_STM32100B_EVAL
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Value Line Device  "
  #define MESSAGE3   "    running on      "
  #define MESSAGE4   "   STM32100B-EVAL   "
#elif defined USE_STM32100E_EVAL
  #define MESSAGE1   " STM32 High Density "
  #define MESSAGE2   " Value Line Device  "
  #define MESSAGE3   "    running on      "
  #define MESSAGE4   "   STM32100E-EVAL   "
#endif
  #define MESSAGE5   " program built with "
  #define MESSAGE6   " Atollic TrueSTUDIO "


/* Private macro */
/* Private variables */
 USART_InitTypeDef USART_InitStructure;

/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;
  //int pin = LED_RED;

  GPIOC_Init();
  led_toggle();
  led_toggle();
  led_toggle();
  led_toggle();
  led_toggle();

  while(1)
  {
	  for(i=0;i<500000;i++)
	  	  ;

	  led_toggle();
  }

}

/* Initialize GPIOA PIN8 */
void GPIOC_Init(void)
{
    /* Configuration info. for PORTA PIN8:
     * - Speed = 50MHz
     * - Push-pull output mode
     */
    GPIO_InitTypeDef gpioc_pin13_config = { GPIO_Pin_13,
                                           GPIO_Speed_50MHz,
                                           GPIO_Mode_Out_PP };

    /* Enable PORT A clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    /* Configure PORTA PIN 13 */
    GPIO_Init(GPIOC, &gpioc_pin13_config);

    /* Turn off LED to start with */
    GPIOC->BSRR = (uint32_t)1 << 13;
}

/* Toggle LED */
void led_toggle(void)
{
    /* If PORTA BIT 8 clear, set it */
    if((GPIOC->ODR & (uint32_t)1<<13) == 0)
    {
        GPIOC->BSRR = (uint32_t)1 << 13;
    }
    /* If PORTA BIT 8 set, clear it */
    else
    {
        GPIOC->BRR = (uint32_t)1 << 13;
    }
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

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

