/*
 * @Author: lanchanghai
 * @Date: 2022-11-18 22:51:12
 * @LastEditors: lanchanghai
 * @LastEditTime: 2022-11-18 23:04:57
 * @FilePath: /STM32F103ZE_Makefile_jicunqi/Drivers/HARDWARE/Inc/stm32f103_gpio.h
 */
#ifndef _STM32F103_GPIO_H
#define _STM32F103_GPIO_H

#include "stm32f10x.h"

#define GPIO_Pin_0   ((u16)0x0001)
#define GPIO_Pin_1   ((u16)0x0002)
#define GPIO_Pin_2   ((u16)0x0004)
#define GPIO_Pin_3   ((u16)0x0008)
#define GPIO_Pin_4   ((u16)0x0010)
#define GPIO_Pin_5   ((u16)0x0020)
#define GPIO_Pin_6   ((u16)0x0040)
#define GPIO_Pin_7   ((u16)0x0080)

#define GPIO_Pin_8   ((u16)0x0100)
#define GPIO_Pin_9   ((u16)0x0200)
#define GPIO_Pin_10  ((u16)0x0400)
#define GPIO_Pin_11  ((u16)0x0800)
#define GPIO_Pin_12  ((u16)0x1000)
#define GPIO_Pin_13  ((u16)0x2000)
#define GPIO_Pin_14  ((u16)0x4000)
#define GPIO_Pin_15  ((u16)0x8000)
#define GPIO_Pin_A11 ((u16)0xffff) //ȫ������

#define GPIOA_ODR_Addr  (GPIOA_BASE+0X0C)
#define GPIOB_ODR_Addr  (GPIOB_BASE+0X0C)
#define GPIOC_ODR_Addr  (GPIOC_BASE+0X0C)
#define GPIOD_ODR_Addr  (GPIOD_BASE+0X0C)
#define GPIOE_ODR_Addr  (GPIOE_BASE+0X0C)
#define GPIOF_ODR_Addr  (GPIOF_BASE+0X0C)
#define GPIOG_ODR_Addr  (GPIOG_BASE+0X0C)

#define GPIOA_IDR_Addr  (GPIOA_BASE+0X08)
#define GPIOB_IDR_Addr  (GPIOB_BASE+0X08)
#define GPIOC_IDR_Addr  (GPIOC_BASE+0X08)
#define GPIOD_IDR_Addr  (GPIOD_BASE+0X08)
#define GPIOE_IDR_Addr  (GPIOE_BASE+0X08)
#define GPIOF_IDR_Addr  (GPIOF_BASE+0X08)
#define GPIOG_IDR_Addr  (GPIOG_BASE+0X08)

#define PAout(n) *(u32 *)((GPIOA_ODR_Addr & 0xF0000000)+0x02000000+((GPIOA_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PBout(n) *(u32 *)((GPIOB_ODR_Addr & 0xF0000000)+0x02000000+((GPIOB_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PCout(n) *(u32 *)((GPIOC_ODR_Addr & 0xF0000000)+0x02000000+((GPIOC_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PDout(n) *(u32 *)((GPIOD_ODR_Addr & 0xF0000000)+0x02000000+((GPIOD_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PEout(n) *(u32 *)((GPIOE_ODR_Addr & 0xF0000000)+0x02000000+((GPIOE_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PFout(n) *(u32 *)((GPIOF_ODR_Addr & 0xF0000000)+0x02000000+((GPIOF_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PGout(n) *(u32 *)((GPIOG_ODR_Addr & 0xF0000000)+0x02000000+((GPIOG_ODR_Addr & 0x00FFFFFF)<<5)+(n<<2))

#define PAin(n) *(u32 *)((GPIOA_IDR_Addr & 0xF0000000)+0x02000000+((GPIOA_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PBin(n) *(u32 *)((GPIOB_IDR_Addr & 0xF0000000)+0x02000000+((GPIOB_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PCin(n) *(u32 *)((GPIOC_IDR_Addr & 0xF0000000)+0x02000000+((GPIOC_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PDin(n) *(u32 *)((GPIOD_IDR_Addr & 0xF0000000)+0x02000000+((GPIOD_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PEin(n) *(u32 *)((GPIOE_IDR_Addr & 0xF0000000)+0x02000000+((GPIOE_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PFin(n) *(u32 *)((GPIOF_IDR_Addr & 0xF0000000)+0x02000000+((GPIOF_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))
#define PGin(n) *(u32 *)((GPIOG_IDR_Addr & 0xF0000000)+0x02000000+((GPIOG_IDR_Addr & 0x00FFFFFF)<<5)+(n<<2))

#define LED1 PGout(6)
#define LED2 PAout(8)
#define LED3 PBout(8)
#define LED4 PBout(9)

void GPIO_SetBits(GPIO_TypeDef *GPIOx,u16 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx,u16 GPIO_Pin);
void LED_Init(void);

#endif



