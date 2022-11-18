#include "SPI.h"

void SPI_Init(void)   //初始化SPI
{
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0x0000ffff;
	GPIOB->CRH|=0x34330000;
  SPI2_CS=1;
	SPI2_CLK=1;
}



//SPI可以同时读取和写入数据，因此一个函数即可满足要求
u8 SPI_ReadWriteByte(u8 txData)
{
    u8 i;
    u8 rxData = 0;

    for(i = 0; i < 8; i++)
    {
        SPI2_CLK=0;
        //delay_us(1);
        //数据发送
        if(txData & 0x80){
            SPI2_MOSI=1;
        }else{
            SPI2_MOSI=0;
        }
        txData <<= 1;
        //delay_us(1);
				
        SPI2_CLK=1;
        //delay_us(1);
        //数据接收
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

