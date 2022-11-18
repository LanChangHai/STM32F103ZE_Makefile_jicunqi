#include "adc.h"

//u16 dianya[10];

void adc_init(void)
{
	RCC->APB2ENR|=1<<3; //pb0 adcͨ��8
	GPIOB->CRL&=0xfffffff0;
	
	RCC->APB2ENR|=1<<2; //ʹ�� PORTA ��ʱ��
  GPIOA->CRL&=0XFF0FFFFF;//PA1 anolog ����
	
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����
	RCC->CFGR&=~(3<<14);   
	RCC->CFGR|=2<<14;  // ��Ƶ������Ϊ6��Ƶ 12Mhz
	
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;
  ADC1->CR2|=1<<20;	    //�������ת��,������������ͨ����ת�����ⲿ�����¼�
	ADC1->CR2&=~(1<<11);   //�Ҷ���
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1��ת���ڹ��������� 	
	ADC1->SMPR2&=~(7<<24);
	ADC1->SMPR2|=7<<24;   //239.5����+12.5=252���� = 21us
	ADC1->CR2|=1<<0;	   //����ADת����	 
	ADC1->CR2|=1<<3;       //ʹ�ܸ�λУ׼  
	while(ADC1->CR2&1<<3); //�ȴ�У׼���� 			 
    //��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        //����ADУ׼	   
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����
	//��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}

u16 Get_Adc(u8 ch)   
{
	//����ת������	  		 
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //��������ת��ͨ��
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

