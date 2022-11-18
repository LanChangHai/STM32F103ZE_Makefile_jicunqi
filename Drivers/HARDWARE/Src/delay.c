#include "delay.h"

static u8 fac_us;
static u16 fac_ms;

void delay_init(u8 SYSCLK)
{
 	SysTick->CTRL&=~(1<<2);					//控制状态寄存器 CLKSOUREC 0 外部时钟源
	fac_us=SYSCLK/8;					  
	fac_ms=(u16)fac_us*1000;				
}		

void delay_us(u16 us)
{
	u32 temp;
	SysTick->LOAD=(u32)(us*fac_us);
	SysTick->VAL=0x00;
	SysTick->CTRL|=0x01;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	
	SysTick->CTRL=0x00;      	 	
	SysTick->VAL =0X00;       				
}

void delay_ms(u16 ms)
{
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms;			
	SysTick->VAL =0x00;           			
	SysTick->CTRL=0x01 ;          			  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	  
	SysTick->CTRL=0x00;      	 			
	SysTick->VAL =0X00;       				
}


