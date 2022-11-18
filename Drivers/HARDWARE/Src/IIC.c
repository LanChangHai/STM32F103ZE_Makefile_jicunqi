#include "IIC.h"

void IIC_GPIO_Init(void)
{
	RCC->APB2ENR|=(1<<3);
	GPIOB->CRL|=0x73000000;
	IIC_SDA=1;	  	  
	IIC_SCL=1;
}

void IIC_Start(void)
{
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;                        //当SCL高电平时，SDA出现一个下跳沿表示IIC总线启动信号
	delay_us(4);
	IIC_SCL=0;      
  delay_us(4);  
}

void IIC_Stop(void)
{
	IIC_SDA=0; 	
	IIC_SCL=1; 
  delay_us(4);
	IIC_SDA=1;                        //当SCL高电平时，SDA出现一个上跳沿表示IIC总线停止信号
	delay_us(5);
}

void IIC_Ack(void)
{
	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=1;
	delay_us(4);
	IIC_SCL=0;
  delay_us(4);
  IIC_SDA=1;
}

void IIC_NAck(void)
{
	IIC_SDA=1;
	delay_us(4);
	IIC_SCL=1;
	delay_us(4);
	IIC_SCL=0;
  delay_us(4);
}

u8 IIC_Wait_Ack(void)
{
	u8 temp;

	IIC_SDA=1;	                  //释放SDA总线
	delay_us(4);
	IIC_SCL=1;	                  //驱动SCL为高电平, 此时器件会返回ACK应答
	delay_us(4);
	if (IIC_SDA_Read)       //读取SDA口线状态
	{
		temp = 1;
	}
	else
	{
		temp = 0;
	}
	IIC_SCL=0;
	delay_us(4);
	return temp;
}

void IIC_Send_Byte(uint8_t Data)
{
	uint8_t BitCnt;

	// 先发送字节的高位bit7 
	for (BitCnt = 0; BitCnt < 8; BitCnt++)
	{		
		if (Data & 0x80)
		{
			IIC_SDA=1;
		}
		else
		{
			IIC_SDA=0;
		}
		delay_us(4);
		IIC_SCL=1;
		delay_us(4);	
		IIC_SCL=0;
		Data <<= 1;	          // 左移一个bit
		delay_us(4);
	}
	IIC_SDA=1;          // 释放IIC总线
}

u8 IIC_Read_Byte(uint8_t ack)
{
	u8 i,temp=0;

  for(i=0;i<8;i++ )
	{
     IIC_SCL=0; 
     delay_us(4);
		 IIC_SCL=1;
     temp<<=1;
     if(IIC_SDA_Read)	            //读取SDA口线状态
		 {
			 temp++;
		 }  
		 delay_us(4); 
   }					 
    if (!ack)
      IIC_NAck();                //发送nACK
    else
      IIC_Ack();                 //发送ACK   
    return temp;
}

