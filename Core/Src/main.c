/*
 * @Author: lanchanghai
 * @Date: 2022-11-18 22:51:00
 * @LastEditors: lanchanghai
 * @LastEditTime: 2022-11-19 00:14:11
 * @FilePath: /STM32F103ZE_Makefile_jicunqi/Core/Src/main.c
 */
#include "stm32f10x.h"
#include "stm32f103_gpio.h"
#include "delay.h"
//#include "chuankou.h"
#include "sys.h"
//#include "SPI.h"
//#include "tim.h"
//#include "oled.h"
//#include "zhongduan.h"
//#include "key.h"
//#include "usart.h"
//#include "bmp.h"
//#include "math.h"
//#include "DAC.h"
//#include "esp_01s.h"
#include "pwm.h"

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* Suppress warning messages */
#if defined(__CC_ARM)
// Suppress warning message: extended constant initialiser used
#pragma diag_suppress 1296
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#endif

/* USER CODE END PM */
int main(void){
	
	Stm32_Clock_Init(9);
	delay_init(72);
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL&=0Xfffff0ff;
	GPIOA->CRL|=0X00000300;
	
	while(1){
		PAout(2)=0;
		delay_ms(1000);
		PAout(2)=1;
		delay_ms(1000);
	}
}
