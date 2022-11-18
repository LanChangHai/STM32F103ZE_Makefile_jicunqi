#include "zhongduan.h"

/*****************************************************/
/*
 下表给出了允许的抢占优先级和次优先级
 加入NVIC_PriorityGroupConfig功能的“优先级分组”配置
  ============================================================================================================================
    NVIC_PriorityGroup   |         NVIC_抢占优先级           |       NVIC_响应优先级       |              说明
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for 抢占优先级 
                         |                                   |                             |   4 bits for 响应优先级
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for 抢占优先级 
                         |                                   |                             |   3 bits for 响应优先级
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for 抢占优先级 
                         |                                   |                             |   2 bits for 响应优先级
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for 抢占优先级 
                         |                                   |                             |   1 bits for 响应优先级
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for 抢占优先级 
                         |                                   |                             |   0 bits for 响应优先级                       
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


void Exti_NVIC_peizhi(u32 GPIOx,u8 Bitx,u8 chufamoshi)  //触发模式 1上升沿触发 2下降沿触发 3任意触发
{
  u8 io=(u8)((((GPIOx&0xffff)>>8)-0x08)/4);
	u8 zuhao,zuweizhi;
	zuhao=Bitx/4;
	zuweizhi=(Bitx%4)*4;
	RCC->APB2ENR|=0x01; //使能复用
  AFIO->EXTICR[zuhao]&=~(0X000F<<zuweizhi); //调用外部中断配置寄存器；先将设置位清零
  AFIO->EXTICR[zuhao]|=io<<zuweizhi;  //写设置
  EXTI->IMR|=1<<Bitx;   //开启相应线中断
  if(chufamoshi&0x01)
	EXTI->RTSR|=1<<Bitx;
  if(chufamoshi&0x02)
  EXTI->FTSR|=1<<Bitx;	
}



