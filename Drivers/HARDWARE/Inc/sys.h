/*
 * @Author: lanchanghai
 * @Date: 2022-11-18 22:54:25
 * @LastEditors: lanchanghai
 * @LastEditTime: 2022-11-18 23:44:53
 * @FilePath: /STM32F103ZE_Makefile_jicunqi/Drivers/HARDWARE/Inc/sys.h
 */
#ifndef   _SYS_H
#define   _SYS_H

#include "stm32f10x.h"


void MYRCC_DeInit(void);
void Stm32_Clock_Init(u8 PLL);


#endif



