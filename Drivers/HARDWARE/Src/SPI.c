#include "SPI.h"

void SPI_Init(void)   //��ʼ��SPI
{
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0x0000ffff;
	GPIOB->CRH|=0x34330000;
  SPI2_CS=1;
	SPI2_CLK=1;
}



//SPI����ͬʱ��ȡ��д�����ݣ����һ��������������Ҫ��
u8 SPI_ReadWriteByte(u8 txData)
{
    u8 i;
    u8 rxData = 0;

    for(i = 0; i < 8; i++)
    {
        SPI2_CLK=0;
        //delay_us(1);
        //���ݷ���
        if(txData & 0x80){
            SPI2_MOSI=1;
        }else{
            SPI2_MOSI=0;
        }
        txData <<= 1;
        //delay_us(1);
				
        SPI2_CLK=1;
        //delay_us(1);
        //���ݽ���
        rxData <<= 1;
        if(SPI2_MISO){
            rxData |= 0x01;
        }
        delay_us(1);
    }
    SPI2_CLK=0;

    return rxData;
}

u8 SPI_ReadByte(void)
{
    return SPI_ReadWriteByte(Dummy_Byte);
}

void SPI_WriteByte(u8 txData)
{
    (void)SPI_ReadWriteByte(txData);
}

