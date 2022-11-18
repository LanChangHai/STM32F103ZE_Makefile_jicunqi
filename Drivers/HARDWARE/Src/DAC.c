#include "DAC.h"

void stm32HD_DACinit(void){
	RCC->APB2ENR|=1<<2; //使能A 时钟 
	RCC->APB1ENR|=1<<29;  
	GPIOA->CRL&=0XFFF0FFFF; 
	GPIOA->CRL|=0X00000000; 
	DAC->CR|=1<<0; //使能 DAC1
	DAC->CR|=1<<1; //DAC1 输出缓存不使能 BOFF1=1
	DAC->CR|=0<<2; //不使用触发功能 TEN1=0
	DAC->CR|=0<<3; //DAC TIM6 TRGO,不过要 TEN1=1 才行
	DAC->CR|=0<<6; //不使用波形发生
	DAC->CR|=0<<8; //屏蔽、幅值设置
	DAC->CR|=0<<12; 
	DAC->DHR12R1=0;
}

void Dac1_Set_Vol(u16 vol)
{
		float temp=vol;
		temp/=1000;
		temp=temp*4096/3.3; //计算 DAC 输出寄存器值
		DAC->DHR12R1=temp;
}
