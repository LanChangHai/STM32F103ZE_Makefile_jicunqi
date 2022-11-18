#ifndef IIC_H
#define IIC_H

#include "delay.h"
#include "stm32f103_gpio.h"
#include "stm32f10x.h"

#define IIC_SDA PBout(7)
#define IIC_SCL PBout(6)
#define IIC_SDA_Read PBin(7)

void IIC_GPIO_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NAck(void);
u8 IIC_Wait_Ack(void);
void IIC_Send_Byte(uint8_t Data);
u8 IIC_Read_Byte(uint8_t ack);

#endif
