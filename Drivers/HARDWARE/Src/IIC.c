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
 	IIC_SDA=0;                        //��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾIIC���������ź�
	delay_us(4);
	IIC_SCL=0;      
  delay_us(4);  
}

void IIC_Stop(void)
{
	IIC_SDA=0; 	
	IIC_SCL=1; 
  delay_us(4);
	IIC_SDA=1;                        //��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾIIC����ֹͣ�ź�
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

	IIC_SDA=1;	                  //�ͷ�SDA����
	delay_us(4);
	IIC_SCL=1;	                  //����SCLΪ�ߵ�ƽ, ��ʱ�����᷵��ACKӦ��
	delay_us(4);
	if (IIC_SDA_Read)       //��ȡSDA����״̬
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

	// �ȷ����ֽڵĸ�λbit7 
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
		Data <<= 1;	          // ����һ��bit
		delay_us(4);
	}
	IIC_SDA=1;          // �ͷ�IIC����
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
     if(IIC_SDA_Read)	            //��ȡSDA����״̬
		 {
			 temp++;
		 }  
		 delay_us(4); 
   }					 
    if (!ack)
      IIC_NAck();                //����nACK
    else
      IIC_Ack();                 //����ACK   
    return temp;
}

