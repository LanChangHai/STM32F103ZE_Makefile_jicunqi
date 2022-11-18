#include "adc.h"

//u16 dianya[10];

void adc_init(void)
{
	RCC->APB2ENR|=1<<3; //pb0 adc通道8
	GPIOB->CRL&=0xfffffff0;
	
	RCC->APB2ENR|=1<<2; //使能 PORTA 口时钟
  GPIOA->CRL&=0XFF0FFFFF;//PA1 anolog 输入
	
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束
	RCC->CFGR&=~(3<<14);   
	RCC->CFGR|=2<<14;  // 分频因子设为6分频 12Mhz
	
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;
  ADC1->CR2|=1<<20;	    //软件控制转换,开启启动规则通道组转换的外部触发事件
	ADC1->CR2&=~(1<<11);   //右对齐
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1个转换在规则序列中 	
	ADC1->SMPR2&=~(7<<24);
	ADC1->SMPR2|=7<<24;   //239.5周期+12.5=252周期 = 21us
	ADC1->CR2|=1<<0;	   //开启AD转换器	 
	ADC1->CR2|=1<<3;       //使能复位校准  
	while(ADC1->CR2&1<<3); //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除  
}

u16 Get_Adc(u8 ch)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道
	while(!(ADC1->SR&1<<1));
	return ADC1->DR;
}

u16 Get_Adc_Average(u8 ch)
{
	u32 temp_val=0;
	for(u8 t=0;t<10;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/10;
} 

