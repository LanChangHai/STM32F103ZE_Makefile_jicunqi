#include "tim.h"

void tim_Init(TIM_TypeDef * TIMx,u16 arr,u16 psc)//ֻ�����ڶ�ʱ��2-7
{
	uint32_t i=(uint32_t) TIMx;
	i=(i-APB1PERIPH_BASE)>>10;
	RCC->APB1ENR|=1<<i;
	TIMx->ARR=arr;  	//�趨�������Զ���װֵ 
	TIMx->PSC=psc;  	//Ԥ��Ƶ������
	TIMx->DIER|=1<<0;   //��������ж�				
	TIMx->CR1|=0x01;    //ʹ�ܶ�ʱ��
}

