#include "DAC.h"

void stm32HD_DACinit(void){
	RCC->APB2ENR|=1<<2; //ʹ��A ʱ�� 
	RCC->APB1ENR|=1<<29;  
	GPIOA->CRL&=0XFFF0FFFF; 
	GPIOA->CRL|=0X00000000; 
	DAC->CR|=1<<0; //ʹ�� DAC1
	DAC->CR|=1<<1; //DAC1 ������治ʹ�� BOFF1=1
	DAC->CR|=0<<2; //��ʹ�ô������� TEN1=0
	DAC->CR|=0<<3; //DAC TIM6 TRGO,����Ҫ TEN1=1 ����
	DAC->CR|=0<<6; //��ʹ�ò��η���
	DAC->CR|=0<<8; //���Ρ���ֵ����
	DAC->CR|=0<<12; 
	DAC->DHR12R1=0;
}

void Dac1_Set_Vol(u16 vol)
{
		float temp=vol;
		temp/=1000;
		temp=temp*4096/3.3; //���� DAC ����Ĵ���ֵ
		DAC->DHR12R1=temp;
}
