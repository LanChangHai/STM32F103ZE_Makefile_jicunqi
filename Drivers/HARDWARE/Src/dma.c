#include "dma.h"

u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 		    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ�����  
void DMA1_Config(DMA_Channel_TypeDef *DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA_CHx->CPAR=cpar; 	 	//DMA1 �����ַ 
	DMA_CHx->CMAR=(u32)cmar; 	//DMA1,�洢����ַ
	DMA1_MEM_LEN=cndtr;      	//����DMA����������
	DMA_CHx->CNDTR=cndtr;    	//DMA1,����������
	DMA_CHx->CCR=0X00000000;	//��λ
	DMA_CHx->CCR&=~(1<<4);  		//�������
	DMA_CHx->CCR|=0<<5;  		//��ͨģʽ
	DMA_CHx->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA_CHx->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA_CHx->CCR|=1<<8; 	 	//�������ݿ��Ϊ16λ
	DMA_CHx->CCR|=1<<10; 		//�洢�����ݿ��16λ
	DMA_CHx->CCR|=1<<12; 		//�е����ȼ�
	DMA_CHx->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ		  	
} 
//����һ��DMA����
void DMA1_Enable(DMA_Channel_TypeDef *DMA_CHx)
{
	DMA_CHx->CCR&=~(1<<0);       //�ر�DMA���� 
	DMA_CHx->CNDTR=DMA1_MEM_LEN; //DMA1,���������� 
	DMA_CHx->CCR|=1<<0;          //����DMA����
}	

