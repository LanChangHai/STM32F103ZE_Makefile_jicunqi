#include "zhongduan.h"

/*****************************************************/
/*
 �±�������������ռ���ȼ��ʹ����ȼ�
 ����NVIC_PriorityGroupConfig���ܵġ����ȼ����顱����
  ============================================================================================================================
    NVIC_PriorityGroup   |         NVIC_��ռ���ȼ�           |       NVIC_��Ӧ���ȼ�       |              ˵��
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for ��ռ���ȼ� 
                         |                                   |                             |   4 bits for ��Ӧ���ȼ�
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for ��ռ���ȼ� 
                         |                                   |                             |   3 bits for ��Ӧ���ȼ�
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for ��ռ���ȼ� 
                         |                                   |                             |   2 bits for ��Ӧ���ȼ�
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for ��ռ���ȼ� 
                         |                                   |                             |   1 bits for ��Ӧ���ȼ�
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for ��ռ���ȼ� 
                         |                                   |                             |   0 bits for ��Ӧ���ȼ�                       
  ============================================================================================================================
*/
/*****************************************************/


void NVIC_fenzu(u8 fenzu)
{
  u32 temp,temp1;
	temp1=((~fenzu)&0x07)<<8;
	temp=SCB->AIRCR;
	temp&=0x0000F8FF;
	temp|=0x05FA0000;
	temp|=temp1;
	SCB->AIRCR=temp;
}


void NVIC_Init(u8 qiangduan,u8 xiangying,u8 zhongduanhao,u8 fenzu)
{
	u32 temp;
	NVIC_fenzu(fenzu);
	temp=qiangduan<<(4-fenzu);
	temp|=xiangying&(0x0f>>fenzu);
	temp&=0x0f;
	NVIC->ISER[zhongduanhao/32]|=(1<<zhongduanhao%32);
	NVIC->IP[zhongduanhao]|=temp<<4;
}


void Exti_NVIC_peizhi(u32 GPIOx,u8 Bitx,u8 chufamoshi)  //����ģʽ 1�����ش��� 2�½��ش��� 3���ⴥ��
{
  u8 io=(u8)((((GPIOx&0xffff)>>8)-0x08)/4);
	u8 zuhao,zuweizhi;
	zuhao=Bitx/4;
	zuweizhi=(Bitx%4)*4;
	RCC->APB2ENR|=0x01; //ʹ�ܸ���
  AFIO->EXTICR[zuhao]&=~(0X000F<<zuweizhi); //�����ⲿ�ж����üĴ������Ƚ�����λ����
  AFIO->EXTICR[zuhao]|=io<<zuweizhi;  //д����
  EXTI->IMR|=1<<Bitx;   //������Ӧ���ж�
  if(chufamoshi&0x01)
	EXTI->RTSR|=1<<Bitx;
  if(chufamoshi&0x02)
  EXTI->FTSR|=1<<Bitx;	
}



