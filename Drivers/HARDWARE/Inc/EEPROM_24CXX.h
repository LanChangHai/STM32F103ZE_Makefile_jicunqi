#ifndef __EEPROM_24CXX_H
#define __EEPROM_24CXX_H

#define C01		127
#define C02		255
#define C04		511
#define C08		1023
#define C16		2047
#define C32		4095
#define C64	    8191
#define C128	16383
#define C256	32767  
#define C512	65535  

#include "IIC.h"
#include "stm32f103_gpio.h"
#include "delay.h"

u8 AT24CXX_RcvOneByte(u16 xinhao,u8 qjdz,u16 Addr);
void AT24CXX_SendOneByte(u16 xinhao,u8 qjdz,u16 Addr,u8 Data);

#endif

