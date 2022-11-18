#include "pwm.h"

void TIM3_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0XF0FFFFFF;
	GPIOA->CRL|=0X0B000000;
//	GPIOC->CRL&=0XF0FFFFFF;	//Pc6输出
//	GPIOC->CRL|=0X0B000000;	
//	RCC->APB2ENR|=1<<0; //启动辅助功能时钟
//	AFIO->MAPR&=0XFFFFF3FF;
//	AFIO->MAPR|=3<<10; //完全重映像 tim3_ch1->pc6
	TIM3->ARR=arr-1; //
	TIM3->PSC=psc-1; //分频系数
	TIM3->CCMR1|=6<<4;  //110pwm模式一
	TIM3->CCMR1|=1<<3;  //输出比较1预装载使能
    TIM3->CCER|=0<<1;	  //高电平为有效电平
	TIM3->CCER|=1<<0;   //使能通道一
    TIM3->CR1=0x0080;   	//使能重装载
	TIM3->CR1|=0x01;    	//使能定时器3 
}

void TIM1_SPWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11;
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;
	GPIOA->CRH&=0XFFFFFFF0;
	GPIOA->CRH|=0X0000000B;
	GPIOB->CRH&=0XFF0FFFFF;
	GPIOB->CRH|=0X00B00000;
	TIM1->ARR=arr-1; //
	TIM1->PSC=psc-1; //分频系数
	TIM1->CCMR1&=0;
	TIM1->CCMR1|=0X68;
	TIM1->CCER&=0;
	TIM1->CCER|=1<<2;
  TIM1->CCER|=1<<0;
  TIM1->BDTR&=0;
	TIM1->BDTR|=1<<15;
//	TIM1->BDTR|=0xAB;
	TIM1->CR1|=1<<7;   	//使能重装载
	TIM1->CR1|=1<<0;    	//使能定时器3 
}

