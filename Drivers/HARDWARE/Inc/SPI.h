/*���ģ��spiЭ�鲿��,ͬ��ʹ�õ�ΪPB13��14��15 �� 3 ����SCK.��MISO��MOSI��CS ʹ���������ʽ��*/


#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "stm32f103_gpio.h"
#include "delay.h"

#define SPI2_CS PBout(12)
#define SPI2_CLK PBout(13)
#define SPI2_MISO PBin(14)
#define SPI2_MOSI PBout(15)

#define Dummy_Byte    0xFF    //��ȡʱMISO���͵����ݣ�����Ϊ��������


void SPI_Init(void);
u8 SPI_ReadWriteByte(u8 txData);
u8 SPI_ReadByte(void);
void SPI_WriteByte(u8 txData);

#endif

