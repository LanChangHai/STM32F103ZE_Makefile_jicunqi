#include "stm32f103_gpio.h"

void GPIO_SetBits(GPIO_TypeDef *GPIOx,u16 GPIO_Pin)
{
	GPIOx->BSRR|=GPIO_Pin;
}

void GPIO_ResetBits(GPIO_TypeDef *GPIOx,u16 GPIO_Pin)
{
	GPIOx->BRR|=GPIO_Pin;
}

void LED_Init(void)
{
	 RCC->APB2ENR|=(1<<8);
   RCC->APB2ENR|=(1<<3);
	 RCC->APB2ENR|=(1<<2);
   GPIOB->CRH|=0X00000033;
	 GPIOA->CRH|=0x00000003;
	 GPIOG->CRL|=0x03000000;
	 GPIOB->BRR|=0x0300;
	 GPIOB->BSRR|=0x0300;
	 GPIOA->BRR|=0x0100;
	 GPIOA->BSRR|=0x0100;
	 GPIOG->BRR|=0x0040;
	 GPIOG->BSRR|=0x0040;
}

