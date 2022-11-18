#ifndef _12864_H
#define _12864_H

#include "stm32f103_gpio.h"
#include "stm32f10x.h"
#include "delay.h"

#define WRITE_CMD	0xF8//Ð´ÃüÁî  
#define WRITE_DAT	0xFA//Ð´Êý¾Ý

#define RW PAout(7)
#define E PAout(6)

void SendByte(u8 byte);
void lcd_GPIO_init(void);
void Lcd_WriteCmd(u8 Cmd );
void Lcd_WriteData(u8 Dat );
void Lcd_Init(void);
void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str);
void LCD_Clear(void);
void LCD_Display_Picture(uint8_t *img);
void LCD_Danzijie(uint8_t x,uint8_t y,u8 zi);

#endif

