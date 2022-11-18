#include "tim.h"

void tim_Init(TIM_TypeDef * TIMx,u16 arr,u16 psc)//只适用于定时器2-7
{
	uint32_t i=(uint32_t) TIMx;
	i=(i-APB1PERIPH_BASE)>>10;
	RCC->APB1ENR|=1<<i;
	TIMx->ARR=arr;  	//设定计数器自动重装值 
	TIMx->PSC=psc;  	//预分频器设置
	TIMx->DIER|=1<<0;   //允许更新中断				
	TIMx->CR1|=0x01;    //使能定时器
}

