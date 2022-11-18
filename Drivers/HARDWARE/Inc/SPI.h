/*软件模拟spi协议部分,同样使用的为PB13、14、15 这 3 个（SCK.、MISO、MOSI，CS 使用软件管理方式）*/


#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "stm32f103_gpio.h"
#include "delay.h"

#define SPI2_CS PBout(12)
#define SPI2_CLK PBout(13)
#define SPI2_MISO PBin(14)
#define SPI2_MOSI PBout(15)

#define Dummy_Byte    0xFF    //读取时MISO发送的数据，可以为任意数据


void SPI_Init(void);
u8 SPI_ReadWriteByte(u8 txData);
u8 SPI_ReadByte(void);
void SPI_WriteByte(u8 txData);

#endif

